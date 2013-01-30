#include <stdlib.h>
#include <iostream>
#include "Chronos.h"
#include "ImageViewers.h"
#include "RipplingMOO.h"
#include "02_Mandelbrot.h"
#include "03_Julia.h"
#include "HeaterMOO.h"
#include "MouseEventImageViewers.h"
#include "RayTracingImageCuda.h"

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
static bool demoAll(void);

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
    //isOk &= useRayTracing();
    isOk &= demoAll();

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
		    RayTracingImageCudaMOO rayTracing(d, d, 0, 0.005, nbSphere, numThreads);
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

bool useHeater ( void ) {
  const float k = 0.1;
  int blindItr = 2;
  HeaterMOO heater ( 600, 600, k, blindItr );
  MouseEventImageViewers viewer ( &heater, true );
  //ImageViewers viewer ( &heater, true );
  //viewer.run();
  ImageViewers::runALL ();
  return true;
}

bool demoAll(void) {
  int width = 300;
  int height = width;

  RipplingMOO rippling ( width, height, 0, 0.5 );
  RayTracingImageCudaMOO rayTracing ( width, height, 0, 0.005, 20 );
  Mandelbrot mandel ( width, height, DomaineMaths ( -2.1f, -1.3f, 0.8f, 1.3f ), 80 );
  Julia julia ( width, height, DomaineMaths ( -1.3f, -1.4f, 1.3f, 1.4f ), 80, -0.12f, 0.85f );
  HeaterMOO heater ( width, height, 0.1f, 1 );

  ImageViewers imageViewerRippling ( &rippling, true, false, 0, 0 );
  ImageViewers imageViewerRayTracing ( &rayTracing, true, false, width , 0 );
  ImageViewers imageViewerMandelbrot ( &mandel, true, true, 0, width + 50 );
  ImageViewers imageViewerJulia ( &julia, true, true, width, width + 50 );
  MouseEventImageViewers imageViewerHeater ( &heater, true, false, 2*width, 0 );

  ImageViewers::runALL ();

  return true;
}
