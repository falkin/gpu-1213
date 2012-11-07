#include "Indice2D.h"
#include "ripplingcompute.h"

__global__ void kernelFillImage ( uchar4* ptrDevImageGL, int w, int h, float t ) {
  int tid = Indice2D::tid ();
  int nbThreads = Indice2D::nbThread ();
  int s = tid;
  int i, j;
  while ( s < h * w ) {
    Indice2D::pixelIJ ( s, w, i, j );
    computeRippling ( ptrDevImageGL[s], w, i, j, t );
    s += nbThreads;
  }
}

void launchKernelFillImage ( uchar4* ptrDevImageGL, int w, int h, float t ) {
  dim3 dg = dim3 ( 16, 1, 1 );
  dim3 db = dim3 ( 32, 1, 1 );
kernelFillImage<<<dg, db>>>(ptrDevImageGL, w, h, t);
}
