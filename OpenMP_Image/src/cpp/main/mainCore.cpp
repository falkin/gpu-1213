#include <stdlib.h>
#include <iostream>
#include "Chronos.h"
#include "ImageViewers.h"
//#include "MouseEventImageViewers.h"
#include "RipplingMOO.h"
#include "02_Mandelbrot.h"
#include "03_Julia.h"
#include "RayTracingImageCuda.h"
//#include "HeaterMOO.h"
using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*         Declaration                     *|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*     Imported        *|
 \*-------------------------------------*/

//extern double ComputePI8 ( unsigned long long intervals, int threads = 0 );
/*--------------------------------------*\
 |*     Public          *|
 \*-------------------------------------*/

int mainCore(void);

/*--------------------------------------*\
 |*     Private         *|
 \*-------------------------------------*/

static bool useRippling(void);
static bool useMandelbrot(void);
static bool useJulia(void);
static bool useHeater(void);
static bool useRayTracing(void);

/*----------------------------------------------------------------------*\
 |*         Implementation                  *|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*     Public          *|
 \*-------------------------------------*/

int mainCore(void)
    {
    bool isOk = true;
    Chronos chrono;
    chrono.start();

    //isOk &= useHello();

    //isOk &= useRippling ();
    //isOk &= useMandelbrot();
    //isOk &= useJulia ();
    //isOk &= useHeater();
    isOk &= useRayTracing();

    cout << "\n-------------------------------------------------" << endl;
    cout << "End Main : isOk = " << isOk << endl;

    return isOk ? EXIT_SUCCESS : EXIT_FAILURE;
    }

/*--------------------------------------*\
 |*     Private         *|
 \*-------------------------------------*/

bool useRippling(void)
    {
    RipplingMOO ripplingA(600, 600, 0, 0.5);

    bool isAnimationEnable = true;
    ImageViewers imageViewer(&ripplingA, isAnimationEnable);
    ImageViewers::runALL();

    return true;
    }

bool useMandelbrot(void)
    {
    float x0 = -2.1;
    float x1 = 0.8;
    float y0 = -1.3;
    float y1 = 1.3;

    Mandelbrot mandel(800, 600, DomaineMaths(x0, y0, x1, y1), 52);
    ImageViewers viewer(&mandel);
    ImageViewers::runALL();
    return true;
    }

bool useJulia(void)
    {
    float x0 = -1.3;
    float x1 = 1.3;
    float y0 = -1.4;
    float y1 = 1.4;

    Julia julia(800, 600, DomaineMaths(x0, y0, x1, y1), 52, -0.12, 0.85);
    ImageViewers viewer(&julia);
    ImageViewers::runALL();
    return true;
    }

bool useRayTracing(void)
    {
    int nbMeasure = 5;
    int maxDimension = 5000;
    Chronos init;
    Chronos core;
    for (int d = 2000; d < maxDimension; d += 500)
	{
	for (int nbSphere = 100; nbSphere < 1000; nbSphere += 200)
	    {
	    for (int numThreads = 1; numThreads < 6; numThreads++)
		{
		for (int i = 0; i < nbMeasure; i++)
		    {
		    cout << d << ",";
		    cout << nbSphere << ",";
		    cout << numThreads << ",";
		    init.start();
		    RayTracingImageCudaMOO rayTracing(d, d, 0, 0.005, nbSphere, 10);
		    cout << init.stop() << ",";

		    core.start();
		    rayTracing.fillImageGL();
		    cout << core.stop() << endl;
		    }
		}
	    }
	}

    return true;
    }

bool useHeater(void)
    {
    const float k = 0.1;
    int blindItr = 2;
//  HeaterMOO heater ( 600, 600, k, blindItr );
//  MouseEventImageViewers viewer ( &heater, true );
    //ImageViewers viewer ( &heater, true );
    //viewer.run();
    ImageViewers::runALL();
    return true;
    }
/*----------------------------------------------------------------------*\
 |*         End                     *|
 \*---------------------------------------------------------------------*/

