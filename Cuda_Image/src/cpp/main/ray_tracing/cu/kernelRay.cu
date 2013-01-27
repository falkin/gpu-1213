#include "Indice2D.h"
#include "compute.h"
#include "Sphere.h"
#include <stdio.h>



__constant__ Sphere ARRAY_DATA[MAX_SPHERE];

__device__ void copyGMtoSM ( Sphere* tabSM, Sphere* tabGM, int n );

extern __shared__ Sphere ptrShareSphereArray[];

__global__ void kernelFillImageRayShared ( uchar4* ptrDevImageGL, int w, int h, float t, Sphere* ptrDevSphereArray, int nbSphere ) {
  int tid = Indice2D::tid ();
  int tidLocal = Indice2D::tidLocalBlock ();
  int nbThreads = Indice2D::nbThread ();

  copyGMtoSM ( ptrShareSphereArray, ptrDevSphereArray, nbSphere );

  int s = tid;
  int i, j;
  while ( s < h * w ) {
    Indice2D::pixelIJ ( s, w, i, j );
    compute ( ptrDevImageGL[s], w, i, j, t, ptrShareSphereArray, nbSphere );
    s += nbThreads;
  }
}

__global__ void kernelFillImageRayConstant ( uchar4* ptrDevImageGL, int w, int h, float t, int nbSphere ) {
  int tid = Indice2D::tid ();
  int tidLocal = Indice2D::tidLocalBlock ();
  int nbThreads = Indice2D::nbThread ();

  int s = tid;
  int i, j;
  while ( s < h * w ) {
    Indice2D::pixelIJ ( s, w, i, j );
    compute ( ptrDevImageGL[s], w, i, j, t, ARRAY_DATA, nbSphere );
    s += nbThreads;
  }
}

__device__ void copyGMtoSM ( Sphere* tabSM, Sphere* tabGM, int n ) {
  int tidLocal = Indice2D::tidLocalBlock ();
  int nbThreadBlock = Indice2D::nbThreadBlock ();

  while ( tidLocal < n ) {
    tabSM[tidLocal] = tabGM[tidLocal];
    tidLocal += nbThreadBlock;
  }
  __syncthreads ();
}

__global__ void kernelFillImageRayGlobal ( uchar4* ptrDevImageGL, int w, int h, float t, Sphere* ptrDevSphereArray, int nbSphere ) {
  int tid = Indice2D::tid ();
  int nbThreads = Indice2D::nbThread ();
  int s = tid;
  int i, j;
  while ( s < h * w ) {
    Indice2D::pixelIJ ( s, w, i, j );
    compute ( ptrDevImageGL[s], w, i, j, t, ptrDevSphereArray, nbSphere );
    s += nbThreads;
  }
}

void launchKernelFillImageRay(uchar4* ptrDevImageGL, int w, int h, float t, Sphere* ptrHostSphereArray, Sphere* ptrDevSphereArray, int nbSphere,
	MemType memType, dim3 dg, dim3 db)
    {
    switch (memType)
	{
	case GLOBAL:
	    kernelFillImageRayGlobal<<<dg, db>>>(ptrDevImageGL, w, h, t, ptrDevSphereArray, nbSphere);
	    break;
	case SHARED:
	    {
	    int nbByte = nbSphere * sizeof(Sphere);
	    kernelFillImageRayShared<<<dg, db, nbByte>>>(ptrDevImageGL, w, h, t, ptrDevSphereArray, nbSphere);
	    break;
	    }
	case CONSTANT:
	    kernelFillImageRayConstant<<<dg, db>>>(ptrDevImageGL, w, h, t, nbSphere);
	    break;
	}
}
