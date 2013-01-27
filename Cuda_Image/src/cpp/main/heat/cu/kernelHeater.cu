#include "Indice2D.h"
#include "cuda_runtime.h"
#include "cudaTools.h"
#include "ColorToolCuda.h"
#include <stdint.h>
#include <stdio.h>

/**
 *
 */
struct CalibreCuda {
  float _slope;
  float _t;
  float _x1;
  float _x2;
  float _y1;
  float _y2;
};

/**
 *
 */
CalibreCuda createCalibreCuda ( const float x1, const float x2, const float y1, const float y2 ) {
  float slope = ( y2 - y1 ) / ( x2 - x1 );
  CalibreCuda calibre = { slope, ( y1 - slope * x1 ), x1, x2, y1, y2 };
  return calibre;
}

/**
 *
 */
__device__ bool isInsideBounds ( const uint32_t borderWLeft, const uint32_t borderWRight, const uint32_t borderHUp,
    const uint32_t borderHDown, const uint32_t i, const uint32_t j ) {
  bool inside = i < borderWRight;
  inside &= i > borderWLeft;
  inside &= j < borderHDown;
  inside &= j > borderHUp;
  return inside;
}

/**
 *
 */
__device__
float calibrate ( const CalibreCuda& calibre, const float x ) {
  return ( calibre._slope * x ) + calibre._t;
}

/*--------------------------------------*\
 |*   GPU Globals                       *|
 \*-------------------------------------*/

/**
 *
 */
__device__ float sumNeighbours ( const float* ptrDevSrc, const uint32_t i, const uint32_t j, const uint32_t w, const uint32_t h ) {
  float sum = 0.0;
  sum += isInsideBounds ( 0, w, 0, h, i - 1, j ) ? ptrDevSrc[Indice2D::ijToS ( i - 1, j, w )] : 0.0f;
  sum += isInsideBounds ( 0, w, 0, h, i + 1, j ) ? ptrDevSrc[Indice2D::ijToS ( i + 1, j, w )] : 0.0f;
  sum += isInsideBounds ( 0, w, 0, h, i, j - 1 ) ? ptrDevSrc[Indice2D::ijToS ( i, j - 1, w )] : 0.0f;
  sum += isInsideBounds ( 0, w, 0, h, i, j + 1 ) ? ptrDevSrc[Indice2D::ijToS ( i, j + 1, w )] : 0.0f;
  return sum;
}

/**
 *
 */
__global__ void kernelHeatErase ( const float* ptrDevSrc, float* ptrDevDest, const uint32_t w, const uint32_t h ) {
  int tid = Indice2D::tid ();
  int nbThreads = Indice2D::nbThread ();
  int s = tid;
  size_t size = h * w;
  while ( s < size ) {
    ptrDevDest[s] = ptrDevSrc[s] != 0.0f ? ptrDevSrc[s] : ptrDevDest[s];
    s += nbThreads;
  }
}

/**
 *
 */
__global__ void kernelHeatDiffuse ( const float* ptrDevSrc, float* ptrDevDest, const uint32_t w, const uint32_t h, const float k ) {
  int tid = Indice2D::tid ();
  int nbThreads = Indice2D::nbThread ();
  int s = tid;
  size_t size = h * w;
  int i, j;
  while ( s < size ) {
    Indice2D::pixelIJ ( s, w, i, j );
    float old = ptrDevSrc[s];
    float neighbours = sumNeighbours ( ptrDevSrc, i, j, w, h );
    ptrDevDest[s] = old + k * ( neighbours - ( 4 * old ) );
    s += nbThreads;
  }
}

/**
 *
 */
__global__ void kernelHeatInitArrays ( float* ptrDevArray, const uint32_t w, const uint32_t h, const float fill ) {
  int tid = Indice2D::tid ();
  int nbThreads = Indice2D::nbThread ();
  int s = tid;
  size_t size = h * w;
  while ( s < size ) {
    ptrDevArray[s] = fill;
    s += nbThreads;
  }
}

/**
 *
 */
__global__ void kernelHeatInitHeaters ( float* ptrDevHeater, const uint32_t w, const uint32_t h, const float fillBig, const float fillSmall,
    const size_t bigSquare, const size_t smallSquare ) {
  int tid = Indice2D::tid ();
  int nbThreads = Indice2D::nbThread ();
  int s = tid;
  size_t size = h * w;
  int i, j;
  size_t halfW = w / 2;
  size_t quarterW = w / 4;
  size_t threeQuarterW = 3 * w / 4;
  while ( s < size ) {
    Indice2D::pixelIJ ( s, w, i, j );
    bool big = isInsideBounds ( halfW - bigSquare, halfW + bigSquare, halfW - bigSquare, halfW + bigSquare, i, j );
    bool small = isInsideBounds ( quarterW - smallSquare, quarterW + smallSquare, quarterW - smallSquare, quarterW + smallSquare, i, j ); // LU => center ( quarterW, quarterW )
    small |= isInsideBounds ( threeQuarterW - smallSquare, threeQuarterW + smallSquare, quarterW - smallSquare, quarterW + smallSquare, i,
        j ); // RU => center ( threeQuarterW, quarterW )
    small |= isInsideBounds ( quarterW - smallSquare, quarterW + smallSquare, threeQuarterW - smallSquare, threeQuarterW + smallSquare, i,
        j ); // LD => center ( quarterW, threeQuarterW )
    small |= isInsideBounds ( threeQuarterW - smallSquare, threeQuarterW + smallSquare, threeQuarterW - smallSquare,
        threeQuarterW + smallSquare, i, j ); // RD => center ( threeQuarterW, threeQuarterW )

    ptrDevHeater[s] = big ? fillBig : ( small ? fillSmall : 0.0 );
    s += nbThreads;
  }
}

/**
 *
 */
__global__ void kernelHeatDisplay ( const float* ptrDevArray, const uint32_t w, const uint32_t h, const CalibreCuda calibre,
    uchar4* ptrDevImageGL ) {
  int tid = Indice2D::tid ();
  int nbThreads = Indice2D::nbThread ();
  int s = tid;
  size_t size = h * w;
  while ( s < size ) {
    float hue = calibrate ( calibre, ptrDevArray[s] );
    ColorToolCuda::HSB_TO_RVB ( hue, 1, 1, ptrDevImageGL[s].x, ptrDevImageGL[s].y, ptrDevImageGL[s].z );
    ptrDevImageGL[s].w = 255;
    s += nbThreads;
  }
}

/*--------------------------------------*\
 |*   CPU Globals                       *|
 \*-------------------------------------*/
static float* ptrDevHeater = NULL;
static float* ptrDevIniter = NULL;
static float* ptrDevArrayA = NULL;
static float* ptrDevArrayB = NULL;
static CalibreCuda calibre = createCalibreCuda ( 0, 1, 0.7, 0 );

/**
 * Initializes 4 arrays to compute heat dispersion :
 * <ul>
 * <li>heaters</li>
 * <li>initial</li>
 * <li>array A</li>
 * <li>array B</li>
 * </ul>
 *
 * Array A and B are used to diffuse heat and to display.
 *
 * @param w width of the image
 * @param h heigth of the image
 * @param k heat dispersion constant
 * @param blintItr number of blind iteration to do
 */
void initKernelHeatDispersion ( const uint32_t w, const uint32_t h, const float k, const uint32_t blindItr ) {
  // Assign memory
  dim3 dg = dim3 ( 16, 1, 1 );
  dim3 db = dim3 ( 32, 1, 1 );
  size_t size = w * h * sizeof(float);
  HANDLE_ERROR ( cudaMalloc ( (void**) &ptrDevHeater, size ) );
  HANDLE_ERROR ( cudaMalloc ( (void**) &ptrDevIniter, size ) );
  HANDLE_ERROR ( cudaMalloc ( (void**) &ptrDevArrayA, size ) );
  HANDLE_ERROR ( cudaMalloc ( (void**) &ptrDevArrayB, size ) );

  // Fill each value with 0s
  kernelHeatInitArrays<<< dg, db >>> ( ptrDevHeater, w, h, 0.0 );
  kernelHeatInitArrays<<< dg, db >>> ( ptrDevIniter, w, h, 0.0 );
  kernelHeatInitArrays<<< dg, db >>> ( ptrDevArrayA, w, h, 0.0 );
  kernelHeatInitArrays<<< dg, db >>> ( ptrDevArrayB, w, h, 0.0 );

  // Init heaters, middle filled with 0, corners squares filled with 0.5
  size_t bigSquare = w / 10;
  size_t smallSquare = w / 20;
  kernelHeatInitHeaters<<< db, dg >>> ( ptrDevHeater, w, h, 1.0, 0.5, bigSquare, smallSquare );

  // last part of initialization, Erase -> Diffuse -> Erase
  kernelHeatErase<<< dg, db >>> ( ptrDevHeater, ptrDevIniter, w, h );
  kernelHeatDiffuse<<< dg, db >>> ( ptrDevIniter, ptrDevArrayA, w, h, k );
  kernelHeatErase<<< dg, db >>> ( ptrDevHeater, ptrDevArrayA, w, h );
  ;// Just to correct auto-formating from Eclipse
}

/**
 *
 */
void launchKernelHeatDispersion ( const uint32_t w, const uint32_t h, const float k, const uint32_t blindItr, uchar4* ptrDevImageGL ) {
  dim3 dg = dim3 ( 16, 1, 1 );
  dim3 db = dim3 ( 32, 1, 1 );
  // a chaque tour (A -> B -> A ...)
  kernelHeatDisplay<<< db, dg >>> ( ptrDevArrayA, w, h, calibre, ptrDevImageGL );
  for ( int i = 0; i < blindItr; i++ ) {
    kernelHeatDiffuse<<< dg, db >>> ( ptrDevArrayA, ptrDevArrayB, w, h, k );
    kernelHeatErase<<< dg, db >>> ( ptrDevHeater, ptrDevArrayB, w, h );
    float* tmp = ptrDevArrayA; // swapping
    ptrDevArrayA = ptrDevArrayB;
    ptrDevArrayB = tmp;
  }

  ; // Just to correct auto-formating from Eclipse
}
