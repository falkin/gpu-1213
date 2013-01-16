#include <stdlib.h>
#include <iostream>
#include "Chronos.h"
#include "cudaTools.h"
#include "ImageCudaViewers.h"
#include "RipplingImageCuda.h"
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
static bool useRayTracing(void);
static bool demoAll(void);
//static bool useMandelbrot ( void );
//static bool useJulia ( void );

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

    //isOk &= useRippling();
    //isOk &= useRayTracing();
    //isOk &= useMandelbrot();
    //isOk &= useJulia ();
    isOk &= demoAll();


    cout << "\n-------------------------------------------------" << endl;
    cout << "End Main : isOk = " << isOk << endl;

    return isOk ? EXIT_SUCCESS : EXIT_FAILURE;
    }

/*--------------------------------------*\
 |*     Private         *|
 \*-------------------------------------*/

bool demoAll(void)
    {
    int deviceId = 0;
    HANDLE_ERROR(cudaSetDevice(deviceId));
    HANDLE_ERROR(cudaGLSetGLDevice(deviceId));

    int width = 300;
    int height = width;

    RipplingImageCudaMOO rippling(width, height, 0, 0.5);
    RayTracingImageCudaMOO rayTracing(width, height, 0, 0.005, 20);

    ImageCudaViewers imageViewerRippling(&rippling, true,false,0,0);
    ImageCudaViewers imageViewerRayTracing(&rayTracing, true,false,width,0);

    ImageCudaViewers::runALL();

    return true;

    }

bool useRippling(void)
    {
    int deviceId = 0;
    HANDLE_ERROR(cudaSetDevice(deviceId));
    HANDLE_ERROR(cudaGLSetGLDevice(deviceId));
    RipplingImageCudaMOO ripplingA(600, 600, 0, 0.5);

    bool isAnimationEnable = true;
    ImageCudaViewers imageViewer(&ripplingA, isAnimationEnable);
    ImageCudaViewers::runALL();

    return true;
    }

bool useHeater(void)
    {

    return true;
    }

bool useRayTracing(void)
    {
    int deviceId = 0;
    HANDLE_ERROR(cudaSetDevice(deviceId));
    HANDLE_ERROR(cudaGLSetGLDevice(deviceId));
    RayTracingImageCudaMOO image(600, 600, 0, 0.005, 20);

    bool isAnimationEnable = true;
    ImageCudaViewers imageViewer(&image, isAnimationEnable);
    ImageCudaViewers::runALL();

    return true;
    }

//bool useMandelbrot(void)
//    {
//    float x0 = -2.1;
//    float x1 = 0.8;
//    float y0 = -1.3;
//    float y1 = 1.3;
//
//    Mandelbrot mandel(800, 600, DomaineMaths(x0, y0, x1, y1),52);
//    ImageViewers viewer(&mandel);
//    ImageViewers::runALL();
//    return true;
//    }
//
//bool useJulia(void)
//    {
//    float x0 = -1.3;
//    float x1 = 1.3;
//    float y0 = -1.4;
//    float y1 = 1.4;
//
//    Julia julia(800, 600, DomaineMaths(x0, y0, x1, y1),52,-0.12,0.85);
//    ImageViewers viewer(&julia);
//    ImageViewers::runALL();
//    return true;
//    }
/*----------------------------------------------------------------------*\
 |*         End                     *|
 \*---------------------------------------------------------------------*/

