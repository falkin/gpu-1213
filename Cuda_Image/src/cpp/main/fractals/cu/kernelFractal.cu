#include "Indice2D.h"
#include "fractal.h"
#include "computeFractals.h"
#include <stdint.h>
#include "DomaineMaths.h"
#include "cuda_runtime.h"
#include "cudaTools.h"
#include <stdio.h>

/**
 *
 */
__global__ void kernelMandelbrot ( uchar4* ptrDevImageGL, const uint32_t w, const uint32_t h, const DomainMathsCuda domain,
    const uint32_t n ) {
  int tid = Indice2D::tid ();
  int nbThreads = Indice2D::nbThread ();
  int s = tid;
  size_t size = h * w;
  int32_t i, j;
  double x, y;
  while ( s < size ) {
    Indice2D::pixelIJ ( s, w, i, j );
    toXY ( domain, i, j, x, y );
    displayMandelbrotXY ( x, y, n, ptrDevImageGL, s );
    s += nbThreads;
  }
}

/**
 *
 */
__global__ void kernelJulia ( uchar4* ptrDevImageGL, const uint32_t w, const uint32_t h, const DomainMathsCuda domain, const uint32_t n,
    const float real_c, const float img_c ) {
  int tid = Indice2D::tid ();
  int nbThreads = Indice2D::nbThread ();
  int s = tid;
  size_t size = h * w;
  int32_t i, j;
  double x, y;
  while ( s < size ) {
    Indice2D::pixelIJ ( s, w, i, j );
    toXY ( domain, i, j, x, y );
    displayJuliaXY ( x, y, n, real_c, img_c, ptrDevImageGL, s );
    s += nbThreads;
  }
}

/**
 *
 */
void launchKernelFillImageFractal ( uchar4* ptrDevImageGL, const uint32_t w, const uint32_t h, const DomaineMaths& domain,
    const FractalType type, const uint32_t n, const float real_c, const float img_c ) {
  dim3 dg = dim3 ( 16, 1, 1 );
  dim3 db = dim3 ( 32, 1, 1 );
  DomainMathsCuda cudaDomain = createDomaineMathsCuda ( domain, w, h );
  switch ( type ) {
  case MANDELBROT:
    kernelMandelbrot<<< dg, db >>>( ptrDevImageGL, w, h, cudaDomain, n );
    break;
  case JULIA:
    kernelJulia<<< dg, db >>>( ptrDevImageGL, w, h, cudaDomain, n, real_c, img_c );
    break;
  case NEWTON:
    break;
  }
}
