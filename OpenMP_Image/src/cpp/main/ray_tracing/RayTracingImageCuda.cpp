#include "RayTracingImageCuda.h"
#include <math.h>
#include "aleaTools.h"
#include "compute.h"
#include <stdio.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

RayTracingImageCudaMOO::RayTracingImageCudaMOO(unsigned int w, unsigned int h, float tStart, float dt, int nbSphere, int numThreads) :
	ImageMOOs(w, h), t(tStart), dt(dt), nbSphere(nbSphere), numThreads(numThreads)
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
	centre.z = uniformeAB(10, 2 * w);
	radius = uniformeAB(10, w / 8);

	hue = uniforme01();
	ptrHostSphereArray[i] = *(new Sphere(centre, radius, hue));
	}
    size_t arraySize = nbSphere * sizeof(Sphere);
    }

RayTracingImageCudaMOO::~RayTracingImageCudaMOO()
    {

    }

void RayTracingImageCudaMOO::animationStep(bool& isNeedUpdateView)
    {
    t += dt;
    fillImageGL();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void RayTracingImageCudaMOO::fillImageGL()
    {
    int w = getW();
    int h = getH();

#pragma omp parallel for num_threads(numThreads)
    for (int i = 1; i <= h; i++)
	{
	for (int j = 1; j <= w; j++)
	    {
	    setPixel(i, j, t);
	    }
	}
    }

void RayTracingImageCudaMOO::setPixel(int i, int j, float t)
    {
    unsigned char R, G, B;
    float3 hsb = compute(i, j, t, ptrHostSphereArray, nbSphere);
    ColorTools::HSB_TO_RGB(hsb.x, hsb.y, hsb.z, R, G, B);
    setRGBA(i, j, R, G, B, 255);
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

