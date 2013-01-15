#include "RayTracingImageCuda.h"
#include <math.h>
#include "aleaTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
extern void launchKernelFillImageRay(uchar4* ptrDevImageGL, int w, int h, float t, Sphere* ptrHostSphereArray, Sphere* ptrDevSphereArray, int nbSphere,
	MemType memType);
/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

RayTracingImageCudaMOO::RayTracingImageCudaMOO(unsigned int w, unsigned int h, float tStart, float dt, int nbSphere) :
	ImageCudaMOOs_A(w, h), t(tStart), dt(dt), nbSphere(nbSphere)
    {

    srand (time(NULL));

ptrHostSphereArray    = new Sphere[nbSphere];
    memType=SHARED;

    float3 centre;
    int radius;
    float hue;
    for (int i = 0; i < nbSphere; i++)
	{
	centre.x = uniformeAB(0, w);
	centre.y = uniformeAB(0, h);
	centre.z = uniformeAB(10, 2*w);
	radius = uniformeAB(10, w/8);

	hue = uniforme01();
	ptrHostSphereArray[i] = *(new Sphere(centre, radius, hue));
	}
    size_t arraySize = nbSphere* sizeof(Sphere);

    switch (memType)
	{
	case GLOBAL:
	case SHARED:
	HANDLE_ERROR(cudaMalloc((void**) &ptrDevSphereArray, arraySize));
	HANDLE_ERROR(cudaMemcpy(ptrDevSphereArray,ptrHostSphereArray,arraySize,cudaMemcpyHostToDevice));
	break;
	case CONSTANT:
	HANDLE_ERROR(cudaMemcpyToSymbol("ARRAY_DATA",ptrHostSphereArray,arraySize,0,cudaMemcpyHostToDevice));
	break;
	}

    }

RayTracingImageCudaMOO::~RayTracingImageCudaMOO()
    {

    }

void RayTracingImageCudaMOO::animationStep(bool& isNeedUpdateView)
    {
    t += dt;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void RayTracingImageCudaMOO::fillImageGL(uchar4* ptrDevImageGL, int w, int h)
    {

    launchKernelFillImageRay(ptrDevImageGL, w, h, t, ptrHostSphereArray, ptrDevSphereArray, nbSphere, memType);
    }

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

