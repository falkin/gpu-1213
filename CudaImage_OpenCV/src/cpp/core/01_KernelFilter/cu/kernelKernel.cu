#include "Indice2D.h"
#include "cuda_runtime.h"
#include "cudaTools.h"
#include <iostream>

// TODO: Check DMA memory from capture
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
texture<uint8_t, 2, cudaReadModeElementType> texBWImage;

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
__global__ void kernelRGBImageToBW_Lightness ( const uchar4* ptrDevRGBImage, const uint32_t w, const uint32_t h, uint8_t* ptrDevBWImage ) {
  int tid = Indice2D::tid ();
  int nbThreads = Indice2D::nbThread ();
  int s = tid;
  size_t size = h * w;
  while ( s < size ) {
    uint8_t minresult, maxresult;
    minOrMax3 ( ptrDevRGBImage[s].x, ptrDevRGBImage[s].y, ptrDevRGBImage[s].z, max, &maxresult );
    minOrMax3 ( ptrDevRGBImage[s].x, ptrDevRGBImage[s].y, ptrDevRGBImage[s].z, min, &minresult );
    uint8_t gray = ( maxresult + minresult ) / 2;
    ptrDevBWImage[s] = gray;
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
__global__ void kernelRGBImageToBW_Average ( const uchar4* ptrDevRGBImage, const uint32_t w, const uint32_t h, uint8_t* ptrDevBWImage ) {
  int tid = Indice2D::tid ();
  int nbThreads = Indice2D::nbThread ();
  int s = tid;
  size_t size = h * w;
  while ( s < size ) {
    uint8_t gray = ( ptrDevRGBImage[s].x + ptrDevRGBImage[s].y + ptrDevRGBImage[s].z ) / 3;
    ptrDevBWImage[s] = gray;
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
__global__ void kernelRGBImageToBW_Luminance ( const uchar4* ptrDevRGBImage, const uint32_t w, const uint32_t h, uint8_t* ptrDevBWImage ) {
  int tid = Indice2D::tid ();
  int nbThreads = Indice2D::nbThread ();
  int s = tid;
  size_t size = h * w;
  const float R_FACTOR = 0.21f;
  const float G_FACTOR = 0.71f;
  const float B_FACTOR = 0.07f;
  while ( s < size ) {
    uint8_t gray = ( ptrDevRGBImage[s].x * R_FACTOR ) + ( ptrDevRGBImage[s].y * G_FACTOR ) + ( ptrDevRGBImage[s].z * B_FACTOR );
    ptrDevBWImage[s] = gray;
    s += nbThreads;
  }
}

/**
 * Displays given black&white image to the OpenGL context.
 *
 * @param ptrDevBWImage black&white image resulting from convolution
 * @param w width of the image
 * @param h heigth of the image
 * @param ptrDevImageGL OpenGL context image
 */
__global__ void kernelDisplayBWImage ( const uint8_t* ptrDevBWImage, const uint32_t w, const uint32_t h, uchar4* ptrDevImageGL ) {
  int tid = Indice2D::tid ();
  int nbThreads = Indice2D::nbThread ();
  int s = tid;
  size_t size = h * w;
  while ( s < size ) {
    ptrDevImageGL[s].w = 255;
    ptrDevImageGL[s].x = ptrDevImageGL[s].y = ptrDevImageGL[s].z = ptrDevBWImage[s];
    s += nbThreads;
  }
}

/**
 * Convolution function using texture.
 *
 * @param kernel the kernel used for convolution
 * @param k number of column from the kernel
 * @param center center point of the kernel
 * @param kHalf half of the kernel column size
 * @param i i-th position of the image
 * @param j j-th position of the image
 */
__device__ float convolutionKernelTexture ( const float* ptrDevKernel, const uint32_t k, const uint32_t center, const uint32_t kHalf,
    const uint32_t i, const uint32_t j ) {
  float SE, SO, NE, NO;
  float CH, CV;
  for ( uint32_t u = 1; u <= kHalf; u++ ) {
    for ( uint32_t v = 1; v <= kHalf; v++ ) {
      SE += ptrDevKernel[( center + k * v ) + u] * tex2D ( texBWImage, i + v, j + u );
      SO += ptrDevKernel[( center + k * v ) - u] * tex2D ( texBWImage, i + v, j - u );
      NE += ptrDevKernel[( center - k * v ) + u] * tex2D ( texBWImage, i - v, j + u );
      NO += ptrDevKernel[( center - k * v ) - u] * tex2D ( texBWImage, i - v, j - u );
    }
  }
  for ( int u = -( kHalf ); u < ( kHalf ); u++ ) {
    CH += ptrDevKernel[center + u] * tex2D ( texBWImage, i, j + u );
    CV += ptrDevKernel[center + k * u] * tex2D ( texBWImage, i + u, j );
  }
  return SE + SO + NE + NO + CH + CV - ( ptrDevKernel[center] * tex2D ( texBWImage, i, j ) );
}

/**
 * Kernel which compute convolution using texture.
 *
 * @param w width of the image
 * @param h heigth of the image
 * @param kernel kernel used for the convolution
 * @param k number of column from the kernel
 * @param
 */
__global__ void kernelConvolutionTexture ( const uint32_t w, const uint32_t h, const float* ptrDevKernel, const uint32_t k,
    uchar4* ptrDevImageGL ) {
  int tid = Indice2D::tid ();
  int nbThreads = Indice2D::nbThread ();
  int s = tid;
  size_t size = h * w;
  int i, j;
  int kHalf = ( k / 2 );
  int center = ( k * kHalf ) + kHalf;
  float convolution;
  while ( s < size ) {
    Indice2D::pixelIJ ( s, w, i, j );
    convolution = convolutionKernelTexture ( ptrDevKernel, k, center, kHalf, i, j );
    ptrDevImageGL[s].w = 255;
    ptrDevImageGL[s].x = ptrDevImageGL[s].y = ptrDevImageGL[s].z = (unsigned char) ( convolution + 64.0f );
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
  size_t kernel_size;
};
static uchar4* ptrDevCudaRGBImage = NULL;
static uint8_t* ptrDevCudaBWImage = NULL;
static float* ptrDevKernel = NULL;
static CudaImagesSizes sizes;

/**
 * Initializes memory and everythings
 *
 * @param w width of the image
 * @param h heigth of the image
 */
void initKernelFillImage ( const uint32_t w, const uint32_t h, const float* kernel, const size_t kernelSize ) {
  size_t rgb_size = sizeof(uchar4) * h * w;
  size_t bw_size = sizeof(uint8_t) * h * w;
  sizes.w = w;
  sizes.h = h;
  sizes.rgb_pitch = sizeof(uchar4) * w;
  sizes.rgb_size = rgb_size;
  sizes.bw_pitch = sizeof(uint8_t) * w;
  sizes.bw_size = bw_size;
  sizes.kernel_size = kernelSize;
  HANDLE_ERROR( cudaMalloc((void**) &ptrDevCudaRGBImage, rgb_size) );
  HANDLE_ERROR( cudaMalloc((void**) &ptrDevCudaBWImage, bw_size ) );
  HANDLE_ERROR( cudaMalloc((void**) &ptrDevKernel, kernelSize) );

  // Copy kernel to global memory
  HANDLE_ERROR( cudaMemcpy( ptrDevKernel, kernel, sizes.kernel_size, cudaMemcpyHostToDevice ) );

  // Create tex, bind tex to ptrDevCudaBWImage
  texBWImage.addressMode[0] = cudaAddressModeClamp;
  texBWImage.addressMode[1] = cudaAddressModeClamp;
  texBWImage.filterMode = cudaFilterModePoint;
  texBWImage.normalized = false; // coordinate not in [0, 1]
  cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc<uint8_t> ();
  HANDLE_ERROR( cudaBindTexture2D(NULL, texBWImage, ptrDevCudaBWImage, channelDesc, w, h, sizes.bw_pitch ) );
}

/**
 *
 */
void freeKernelFillImageKernel () {

}

/**
 * Launches kernel which fill image.
 * Kernel called are:
 * <ul>
 * <ol>RGB to BW kernel (3 algorithms)</ol>
 * <ol>Convolution kernel (different memory usage)</ol>
 * </ul>
 *
 * TODO:
 * - Histogram from image
 * - Frangi Filter impl. in CUDA
 *
 * @param ptrDevImageGL OpenGL context image (DEVICE)
 * @param ptrCudaImage image read from video (HOST)
 * @param w width of the image
 * @param h heigth of the image
 */
void launchKernelFillImageKernel ( uchar4* ptrDevImageGL, const uchar4* ptrCudaImage, const uint32_t w, const uint32_t h ) {
  HANDLE_ERROR( cudaMemcpy( ptrDevCudaRGBImage, ptrCudaImage, sizes.rgb_size, cudaMemcpyHostToDevice ) );
  dim3 dg = dim3 ( 16, 1, 1 );
  dim3 db = dim3 ( 32, 1, 1 );
  kernelRGBImageToBW_Lightness<<< dg, db >>> ( ptrDevCudaRGBImage, w, h, ptrDevCudaBWImage );
  //HANDLE_ERROR( cudaDeviceSynchronize() );
  kernelConvolutionTexture<<< dg, db >>> ( w, h, ptrDevKernel, 9, ptrDevImageGL );
  //kernelDisplayBWImage<<< dg, db >>> ( ptrDevCudaBWImage, w, h, ptrDevImageGL );
  // TODO: Use switch to launch memory cases
  ;//
}
