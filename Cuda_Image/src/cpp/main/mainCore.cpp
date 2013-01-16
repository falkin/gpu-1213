#include <stdlib.h>
#include <iostream>
#include "Chronos.h"
#include "cudaTools.h"
#include "ImageCudaViewers.h"
#include "RipplingImageCuda.h"
#include "RayTracingImageCuda.h"
#include "Chronos.h"
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
static bool useRayTracingMeasure(void);
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
    isOk &= useRayTracingMeasure();
    //isOk &= useMandelbrot();
    //isOk &= useJulia ();
    //isOk &= demoAll();

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
    RayTracingImageCudaMOO rayTracing(width, height, 0, 0.005, 50);

    ImageCudaViewers imageViewerRippling(&rippling, true, false, 0, 0);
    ImageCudaViewers imageViewerRayTracing(&rayTracing, true, false, width, 0);

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
    int deviceId = 5;
    HANDLE_ERROR(cudaSetDevice(deviceId));
    HANDLE_ERROR(cudaGLSetGLDevice(deviceId));
    RayTracingImageCudaMOO image(600, 600, 0, 0.005, 1500, SHARED);

    bool isAnimationEnable = true;
    ImageCudaViewers imageViewer(&image, isAnimationEnable);
    ImageCudaViewers::runALL();

    return true;

    }

bool useRayTracingMeasure(void)
    {
    int deviceId = 4;
    HANDLE_ERROR(cudaSetDevice(deviceId));
    HANDLE_ERROR(cudaGLSetGLDevice(deviceId));
    int maxDimension = 10000;
    int nbMeasures = 1;

    // Init chronos
    Chronos kernelChrono;
    Chronos initChrono;
    Chronos getDataChrono;

    cout.precision(10);

    dim3 dg = dim3(16, 1, 1);
    dim3 db = dim3(32, 1, 1);

    for (int d = 2000; d < maxDimension; d += 1000)
	{
	size_t sizeImageOctet = d * d * sizeof(uchar4);
	unsigned char* ptrHostImage = new unsigned char[sizeImageOctet];

	uchar4* ptrDevImage = NULL;
	HANDLE_ERROR(cudaMalloc((void**) &ptrDevImage, sizeImageOctet));

	for (int nbSphere = 100; nbSphere < MAX_SPHERE; nbSphere += 500)
	    {
	    for (int memType = 0; memType < NBMEMTYPE; memType++)
		{
		for (int i = 0; i < nbMeasures; i++)
		    {
		    cout << memType << ",";
		    cout << d << ",";
		    cout << nbSphere << ",";
		    initChrono.start();
		    RayTracingImageCudaMOO image(d, d, 0, 0.005, 100, (MemType) memType, dg, db);
		    HANDLE_ERROR(cudaDeviceSynchronize());
		    initChrono.stop();
		    cout << initChrono.stop() << ",";

		    kernelChrono.start();
		    image.fillImageGL(ptrDevImage, d, d);
		    HANDLE_ERROR(cudaDeviceSynchronize());
		    cout << kernelChrono.stop() << ",";

		    getDataChrono.start();
		    HANDLE_ERROR(cudaMemcpy(ptrHostImage, ptrDevImage, sizeImageOctet, cudaMemcpyDeviceToHost));
		    HANDLE_ERROR(cudaDeviceSynchronize());
		    cout << getDataChrono.stop() << endl;
		    }
		}
	    }
	HANDLE_ERROR(cudaFree(ptrDevImage));
	}
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

