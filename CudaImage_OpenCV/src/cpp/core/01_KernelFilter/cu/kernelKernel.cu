#include "Indice2D.h"
#include "cuda_runtime.h"
#include "cudaTools.h"
#include "KernelFilterImpl.h"
#include "Chronos.h"
#include <iostream>

/*--------------------------------------*\
 |*   UTILS                             *|
 \*-------------------------------------*/
typedef bool (*compare) ( const uint8_t val1, const uint8_t val2 );

__device__ bool min ( const uint8_t val1, const uint8_t val2 ) {
  return val1 > val2;
}

__device__ bool max ( const uint8_t val1, const uint8_t val2 ) {
  return val1 < val2;
}

/**
 * Computes min-or-max using comparaison function.
 *
 * @param val1 the first value to compare
 * @param val2 the second value to compare
 * @param comp the function used to compare
 * @param result the result from min-or-max computation
 */
__device__ void minOrMax ( const uint8_t val1, const uint8_t val2, const compare comp, uint8_t* result ) {
  *result = val1;
  if ( comp ( val1, val2 ) ) {
    *result = val2;
  }
}

/**
 * Computes Min-or-Max from RGB channels.
 *
 * @param r red channel
 * @param g green channel
 * @param b blue channel
 * @param comp compare function
 * @param result resulting value from comparaison
 */
__device__ void minOrMax3 ( const uint8_t r, const uint8_t g, const uint8_t b, const compare comp, uint8_t* result ) {
  uint8_t resultrg, resultgb;
  minOrMax ( r, g, comp, &resultrg );
  minOrMax ( g, b, comp, &resultgb );
  minOrMax ( resultrg, resultgb, comp, result );
}

/*--------------------------------------*\
 |*   GPU Globals                       *|
 \*-------------------------------------*/
texture<uchar4, 2, cudaReadModeElementType> texBWImage;
__constant__ float k_KERNEL[81];

/**
 * Computes Grayscale image from RGB image.
 * <p> Uses lightness algorithm:
 * <pre>
 * bw = (max(R, G, B) + min(R, G, B)) / 2
 * </pre>
 *
 * @param ptrDevRGBImage RGB image read from video
 * @param w width of the image
 * @param h height of the image
 * @param ptrDevBWImage black&white image computed
 */
__global__ void kernelRGBImageToBW_Lightness ( const uchar4* ptrDevRGBImage, const uint32_t w, const uint32_t h, uchar4* ptrDevBWImage ) {
  int tid = Indice2D::tid ();
  int nbThreads = Indice2D::nbThread ();
  int s = tid;
  size_t size = h * w;
  while ( s < size ) {
    uint8_t minresult, maxresult;
    minOrMax3 ( ptrDevRGBImage[s].x, ptrDevRGBImage[s].y, ptrDevRGBImage[s].z, max, &maxresult );
    minOrMax3 ( ptrDevRGBImage[s].x, ptrDevRGBImage[s].y, ptrDevRGBImage[s].z, min, &minresult );
    uint8_t gray = ( maxresult + minresult ) / 2;
    ptrDevBWImage[s].x = ptrDevBWImage[s].y = ptrDevBWImage[s].z = ptrDevBWImage[s].w = gray;
    s += nbThreads;
  }
}

/**
 * Computes Grayscale image from RGB image.
 * <p> Uses average algorithm:
 * <pre>
 * bw = (R + G + B) / 3
 * </pre>
 *
 * @param ptrDevRGBImage RGB image read from video
 * @param w width of the image
 * @param h height of the image
 * @param ptrDevBWImage black&white image computed
 */
__global__ void kernelRGBImageToBW_Average ( const uchar4* ptrDevRGBImage, const uint32_t w, const uint32_t h, uchar4* ptrDevBWImage ) {
  int tid = Indice2D::tid ();
  int nbThreads = Indice2D::nbThread ();
  int s = tid;
  size_t size = h * w;
  while ( s < size ) {
    uint8_t gray = ( ptrDevRGBImage[s].x + ptrDevRGBImage[s].y + ptrDevRGBImage[s].z ) / 3;
    ptrDevBWImage[s].x = ptrDevBWImage[s].y = ptrDevBWImage[s].z = ptrDevBWImage[s].w = gray;
    s += nbThreads;
  }
}

/**
 * Computes Grayscale image from RGB image.
 * <p> Uses lightness algorithm:
 * <pre>
 * bw = (0.21 * R) + (0.71 * G) + (0.07 * B)
 * </pre>
 *
 * @param ptrDevRGBImage RGB image read from video
 * @param w width of the image
 * @param h height of the image
 * @param ptrDevBWImage black&white image computed
 */
__global__ void kernelRGBImageToBW_Luminance ( const uchar4* ptrDevRGBImage, const uint32_t w, const uint32_t h, uchar4* ptrDevBWImage ) {
  int tid = Indice2D::tid ();
  int nbThreads = Indice2D::nbThread ();
  int s = tid;
  size_t size = h * w;
  const float R_FACTOR = 0.21f;
  const float G_FACTOR = 0.71f;
  const float B_FACTOR = 0.07f;
  while ( s < size ) {
    uint8_t gray = ( ptrDevRGBImage[s].x * R_FACTOR ) + ( ptrDevRGBImage[s].y * G_FACTOR ) + ( ptrDevRGBImage[s].z * B_FACTOR );
    ptrDevBWImage[s].x = ptrDevBWImage[s].y = ptrDevBWImage[s].z = ptrDevBWImage[s].w = gray;
    s += nbThreads;
  }
}

/**
 * Convolution function using texture for the image and global memory for the kernel.
 *
 * @param kernel the kernel used for convolution
 * @param k number of column from the kernel
 * @param center center point of the kernel
 * @param kHalf half of the kernel column size
 * @param i i-th position of the image
 * @param j j-th position of the image
 */
__device__ float convolutionKernelGlobalImageTexture ( const float* ptrDevKernel, const uint32_t k, const uint32_t center,
    const uint32_t kHalf, const uint32_t i, const uint32_t j ) {
  float sum = 0.0f;
  for ( int v = 1; v <= kHalf; v++ ) {
    for ( int u = 1; u <= kHalf; u++ ) {
      sum += ptrDevKernel[center + ( v * k ) + u] * tex2D ( texBWImage, j + v, i + u ).x;
      sum += ptrDevKernel[center + ( v * k ) - u] * tex2D ( texBWImage, j + v, i - u ).x;
      sum += ptrDevKernel[center - ( v * k ) + u] * tex2D ( texBWImage, j - v, i + u ).x;
      sum += ptrDevKernel[center - ( v * k ) - u] * tex2D ( texBWImage, j - v, i - u ).x;
    }
  }
  for ( int u = -k / 2; u < k / 2; u++ ) {
    sum += ptrDevKernel[center + u] * tex2D ( texBWImage, j, i + u ).x;
    sum += ptrDevKernel[center + k * u] * tex2D ( texBWImage, j + u, i ).x;
  }
  sum += ( ptrDevKernel[center] * tex2D ( texBWImage, j, i ).x ); // Center computed twice
  return sum;
}

/**
 * Kernel stored in global memory which compute convolution using texture mapping to the image.
 *
 * @param w width of the image
 * @param h heigth of the image
 * @param kernel kernel used for the convolution
 * @param k number of column from the kernel
 * @param ptrDevCudaImageConvolution the convolution result
 */
__global__ void kernelConvolutionGlobalImageTexture ( const uint32_t w, const uint32_t h, const float* ptrDevKernel, const uint32_t k,
    float* ptrDevCudaImageConvolution ) {
  int tid = Indice2D::tid ();
  int nbThreads = Indice2D::nbThread ();
  int s = tid;
  size_t size = h * w;
  int i, j;
  int kHalf = ( k / 2 );
  int center = k * ( k / 2 ) + kHalf;
  float convolution;
  while ( s < size ) {
    Indice2D::pixelIJ ( s, w, i, j );
    convolution = convolutionKernelGlobalImageTexture ( ptrDevKernel, k, center, kHalf, i, j );
    ptrDevCudaImageConvolution[s] = convolution;
    s += nbThreads;
  }
}

/**
 * Convolution function using texture for the image and constant memory for the kernel.
 *
 * @param kernel the kernel used for convolution
 * @param k number of column from the kernel
 * @param center center point of the kernel
 * @param kHalf half of the kernel column size
 * @param i i-th position of the image
 * @param j j-th position of the image
 */
__device__ float convolutionKernelConstantImageTexture ( const uint32_t k, const uint32_t center, const uint32_t kHalf, const uint32_t i,
    const uint32_t j ) {
  float sum = 0.0f;
  for ( int v = 1; v <= kHalf; v++ ) {
    for ( int u = 1; u <= kHalf; u++ ) {
      sum += k_KERNEL[center + ( v * k ) + u] * tex2D ( texBWImage, j + v, i + u ).x;
      sum += k_KERNEL[center + ( v * k ) - u] * tex2D ( texBWImage, j + v, i - u ).x;
      sum += k_KERNEL[center - ( v * k ) + u] * tex2D ( texBWImage, j - v, i + u ).x;
      sum += k_KERNEL[center - ( v * k ) - u] * tex2D ( texBWImage, j - v, i - u ).x;
    }
  }
  for ( int u = -k / 2; u < k / 2; u++ ) {
    sum += k_KERNEL[center + u] * tex2D ( texBWImage, j, i + u ).x;
    sum += k_KERNEL[center + k * u] * tex2D ( texBWImage, j + u, i ).x;
  }
  sum += ( k_KERNEL[center] * tex2D ( texBWImage, j, i ).x ); // Center computed twice.
  return sum;
}

/**
 * Kernel stored in global memory which compute convolution using texture mapping to the image.
 *
 * @param w width of the image
 * @param h heigth of the image
 * @param kernel kernel used for the convolution
 * @param k number of column from the kernel
 * @param ptrDevCudaImageConvolution the convolution result
 */
__global__ void kernelConvolutionConstantImageTexture ( const uint32_t w, const uint32_t h, const uint32_t k,
    float* ptrDevCudaImageConvolution ) {
  int tid = Indice2D::tid ();
  int nbThreads = Indice2D::nbThread ();
  int s = tid;
  size_t size = h * w;
  int i, j;
  int kHalf = ( k / 2 );
  int center = k * ( k / 2 ) + kHalf;
  float convolution;
  while ( s < size ) {
    Indice2D::pixelIJ ( s, w, i, j );
    convolution = convolutionKernelConstantImageTexture ( k, center, kHalf, i, j );
    ptrDevCudaImageConvolution[s] = convolution;
    s += nbThreads;
  }
}

/**
 * Convolution function using texture for the image and constant memory for the kernel.
 *
 * @param kernel the kernel used for convolution
 * @param k number of column from the kernel
 * @param center center point of the kernel
 * @param kHalf half of the kernel column size
 * @param i i-th position of the image
 * @param j j-th position of the image
 */
__device__ float convolutionKernelConstantImageTexture_mul24 ( const uint32_t k, const uint32_t center, const uint32_t kHalf,
    const uint32_t i, const uint32_t j ) {
  float sum = 0.0f;
  for ( int v = 1; v <= kHalf; v++ ) {
    for ( int u = 1; u <= kHalf; u++ ) {
      sum += __mul24 ( k_KERNEL[center + ( v * k ) + u], tex2D ( texBWImage, j + v, i + u ).x );
      sum += __mul24 ( k_KERNEL[center + ( v * k ) - u], tex2D ( texBWImage, j + v, i - u ).x );
      sum += __mul24 ( k_KERNEL[center - ( v * k ) + u], tex2D ( texBWImage, j - v, i + u ).x );
      sum += __mul24 ( k_KERNEL[center - ( v * k ) - u], tex2D ( texBWImage, j - v, i - u ).x );
    }
  }
  for ( int u = -k / 2; u < k / 2; u++ ) {
    sum += __mul24 ( k_KERNEL[center + u], tex2D ( texBWImage, j, i + u ).x );
    sum += __mul24 ( k_KERNEL[center + k * u], tex2D ( texBWImage, j + u, i ).x );
  }
  sum += ( __mul24 ( k_KERNEL[center], tex2D ( texBWImage, j, i ).x ) ); // Center computed twice.
  return sum;
}

/**
 * Kernel stored in global memory which compute convolution using texture mapping to the image.
 *
 * @param w width of the image
 * @param h heigth of the image
 * @param kernel kernel used for the convolution
 * @param k number of column from the kernel
 * @param ptrDevCudaImageConvolution the convolution result
 */
__global__ void kernelConvolutionConstantImageTexture_mul24 ( const uint32_t w, const uint32_t h, const uint32_t k,
    float* ptrDevCudaImageConvolution ) {
  int tid = Indice2D::tid ();
  int nbThreads = Indice2D::nbThread ();
  int s = tid;
  size_t size = h * w;
  int i, j;
  int kHalf = ( k / 2 );
  int center = k * ( k / 2 ) + kHalf;
  float convolution;
  while ( s < size ) {
    Indice2D::pixelIJ ( s, w, i, j );
    convolution = convolutionKernelConstantImageTexture ( k, center, kHalf, i, j );
    ptrDevCudaImageConvolution[s] = convolution;
    s += nbThreads;
  }
}

/**
 * Displays given black&white image to the OpenGL context.
 *
 * @param ptrDevConvolution image resulting from convolution
 * @param w width of the image
 * @param h heigth of the image
 * @param ptrDevImageGL OpenGL context image
 */
__global__ void kernelDisplayConvolution ( const float* ptrDevConvolution, const uint32_t w, const uint32_t h, uchar4* ptrDevImageGL ) {
  int tid = Indice2D::tid ();
  int nbThreads = Indice2D::nbThread ();
  int s = tid;
  size_t size = h * w;
  int i, j;
  while ( s < size ) {
    Indice2D::pixelIJ ( s, w, i, j );
    ptrDevImageGL[s].w = 255;
    ptrDevImageGL[s].x = ptrDevImageGL[s].y = ptrDevImageGL[s].z = (uint8_t) ( ptrDevConvolution[s] );
    s += nbThreads;
  }
}

/*--------------------------------------*\
 |*   CPU Globals                       *|
 \*-------------------------------------*/
struct CudaImagesSizes {
  uint32_t w;
  uint32_t h;
  size_t rgb_pitch;
  size_t rgb_size;
  size_t bw_pitch;
  size_t bw_size;
  size_t conv_size;
  size_t kernel_size;
};
static uchar4* ptrDevCudaRGBImage = NULL;
static uchar4* ptrDevCudaBWImage = NULL;
static float* ptrDevKernel = NULL;
static float* ptrDevCudaImageConvolution = NULL;
static CudaImagesSizes sizes;

/**
 * Initializes memory and everythings
 *
 * @param w width of the image
 * @param h heigth of the image
 */
void initKernelFillImage ( const uint32_t w, const uint32_t h, const float* kernel, const size_t kernelSize ) {
  size_t rgb_size = sizeof(uchar4) * h * w;
  size_t bw_size = sizeof(uchar4) * h * w;
  size_t conv_size = sizeof(float) * h * w;
  sizes.w = w;
  sizes.h = h;
  sizes.rgb_pitch = sizeof(uchar4) * w;
  sizes.rgb_size = rgb_size;
  sizes.bw_pitch = sizeof(uchar4) * w;
  sizes.bw_size = bw_size;
  sizes.conv_size = conv_size;
  sizes.kernel_size = kernelSize * sizeof(float);
  HANDLE_ERROR( cudaMalloc((void**) &ptrDevCudaRGBImage, rgb_size) );
  HANDLE_ERROR( cudaMalloc((void**) &ptrDevCudaBWImage, bw_size ) );
  HANDLE_ERROR( cudaMalloc((void**) &ptrDevCudaImageConvolution, conv_size ) );
  HANDLE_ERROR( cudaMalloc((void**) &ptrDevKernel, sizes.kernel_size) );

// Copy kernel to global memory
  HANDLE_ERROR( cudaMemcpy( ptrDevKernel, kernel, sizes.kernel_size, cudaMemcpyHostToDevice ) );
  HANDLE_ERROR( cudaMemcpyToSymbol("k_KERNEL", kernel, sizes.kernel_size, 0, cudaMemcpyHostToDevice ) );

// Create tex, bind tex to ptrDevCudaBWImage
  texBWImage.addressMode[0] = cudaAddressModeWrap;
  texBWImage.addressMode[1] = cudaAddressModeWrap;
  //texBWImage.filterMode = cudaFilterModePoint;
  texBWImage.normalized = false; // coordinate not in [0, 1]
  cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc<uchar4> ();
  HANDLE_ERROR( cudaBindTexture2D(NULL, &texBWImage, ptrDevCudaBWImage, &channelDesc, w, h, sizes.bw_pitch ) );
}

/**
 *
 */
void freeKernelFillImageKernel () {
  //HANDLE_ERROR (  );
}

/**
 * Launches kernel which fill image.
 * Kernel called are:
 * <ul>
 * <ol>RGB to BW kernel (3 algorithms)</ol>
 * <ol>Convolution kernel (different memory usage)</ol>
 * </ul>
 *
 * @param ptrDevImageGL OpenGL context image (DEVICE)
 * @param ptrCudaImage image read from video (HOST)
 * @param w width of the image
 * @param h heigth of the image
 */
double launchKernelFillImageKernel ( uchar4* ptrDevImageGL, const uchar4* ptrCudaImage, const uint32_t w, const uint32_t h,
    const KernelKind kind, const GrayscaleMethod grayscale, const dim3 dg, const dim3 db ) {
  Chronos chrono;
  HANDLE_ERROR( cudaMemcpy( ptrDevCudaRGBImage, ptrCudaImage, sizes.rgb_size, cudaMemcpyHostToDevice ) );
  chrono.start ();
  switch ( grayscale ) {
  default:
  case AVERAGE:
    kernelRGBImageToBW_Average<<< dg, db >>> ( ptrDevCudaRGBImage, w, h, ptrDevCudaBWImage );
    break;
  case LIGHTNESS:
    kernelRGBImageToBW_Lightness<<< dg, db >>> ( ptrDevCudaRGBImage, w, h, ptrDevCudaBWImage );
    break;
  case LUMINANCE:
    kernelRGBImageToBW_Luminance<<< dg, db >>> ( ptrDevCudaRGBImage, w, h, ptrDevCudaBWImage );
    break;
  }
  switch ( kind ) {
  default:
  case TEXTURE_GLOBAL:
    kernelConvolutionGlobalImageTexture<<< dg, db >>> ( w, h, ptrDevKernel, 9, ptrDevCudaImageConvolution );
    break;
  case TEXTURE_CONSTANT:
    kernelConvolutionConstantImageTexture<<< dg, db >>> ( w, h, 9, ptrDevCudaImageConvolution );
    break;
  case TEXTURE_CONSTANT_MUL24:
    kernelConvolutionConstantImageTexture_mul24<<< dg, db >>> ( w, h, 9, ptrDevCudaImageConvolution );
    break;
  }
  HANDLE_ERROR( cudaDeviceSynchronize() );
  double time = chrono.stop ();
  kernelDisplayConvolution<<< dg, db >>> ( ptrDevCudaImageConvolution, w, h, ptrDevImageGL );
  ; //
  return time;
}
