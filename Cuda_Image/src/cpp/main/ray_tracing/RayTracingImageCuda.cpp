#include "RayTracingImageCuda.h"
#include <math.h>
#include "aleaTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
extern void launchKernelFillImageRay(uchar4* ptrDevImageGL, int w, int h, float t, Sphere* ptrHostSphereArray, Sphere* ptrDevSphereArray, int nbSphere);
/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

RayTracingImageCudaMOO::RayTracingImageCudaMOO(unsigned int w, unsigned int h, float tStart, float dt, int nbSphere) :
	ImageCudaMOOs_A(w, h), t(tStart), dt(dt), nbSphere(nbSphere)
    {

    srand(time(NULL));

    ptrHostSphereArray = new Sphere[nbSphere];


    float3 centre;
    int radius;
    float hue;
    for (int i = 0; i < nbSphere; i++)
	{
	centre.x = uniformeAB(0, w);
	centre.y = uniformeAB(0, h);
	centre.z = uniformeAB(0, w + h);
	radius = uniformeAB(15, 50);
	hue = uniforme01();
	ptrHostSphereArray[i] = *(new Sphere(centre, radius, hue));
	}
    size_t arraySize = nbSphere* sizeof(Sphere);
    HANDLE_ERROR(cudaMalloc((void**) &ptrDevSphereArray, arraySize));
    HANDLE_ERROR(cudaMemcpy(ptrDevSphereArray,ptrHostSphereArray,arraySize,cudaMemcpyHostToDevice));

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
    launchKernelFillImageRay(ptrDevImageGL, w, h, t, ptrHostSphereArray, ptrDevSphereArray,nbSphere);
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

