#include "Indice2D.h"
#include "compute.h"
#include "Sphere.h"


__global__ void kernelFillImageRay ( uchar4* ptrDevImageGL, int w, int h, float t , Sphere* ptrDevSphereArray, int nbSphere) {
  int tid = Indice2D::tid ();
  int nbThreads = Indice2D::nbThread ();
  int s = tid;
  int i, j;
  while ( s < h * w ) {
    Indice2D::pixelIJ ( s, w, i, j );
    compute( ptrDevImageGL[s], w, i, j, t ,ptrDevSphereArray, nbSphere);
    s += nbThreads;
  }
}

void launchKernelFillImageRay ( uchar4* ptrDevImageGL, int w, int h, float t, Sphere* ptrHostSphereArray, Sphere* ptrDevSphereArray,int nbSphere ) {
  dim3 dg = dim3 ( 16, 1, 1 );
  dim3 db = dim3 ( 32, 1, 1 );
kernelFillImageRay<<<dg, db>>>(ptrDevImageGL, w, h, t, ptrDevSphereArray, nbSphere);
}
