#include <stdlib.h>
#include <iostream>
#include "Chronos.h"
#include "cudaTools.h"
#include "ImageCudaViewers.h"
#include "RipplingImageCuda.h"
#include "RayTracingImageCuda.h"
#include "Mandelbrot.h"
#include "Julia.h"
#include "HeaterImageCuda.h"
#include "Chronos.h"

using std::cout;
using std::endl;

int mainCore ( void );

static bool useRippling ( void );
static bool useRayTracing ( void );
static bool useRayTracingMeasure(void);
static bool useMandelbrot ( void );
static bool useJulia ( void );
static bool useHeater ( void );
static bool demoAll ( void );

int mainCore ( void ) {
  bool isOk = true;
  Chronos chrono;
  chrono.start ();

  //isOk &= useHello();

  //isOk &= useRippling();
  //isOk &= useRayTracing();
  //isOk &= useRayTracingMeasure();
  //isOk &= useMandelbrot ();
  //isOk &= useJulia ();
  //isOk &= useHeater ();
  isOk &= demoAll ();

  cout << "\n-------------------------------------------------" << endl;
  cout << "End Main : isOk = " << isOk << endl;

  return isOk ? EXIT_SUCCESS : EXIT_FAILURE;
}

bool demoAll ( void ) {
  int deviceId = 0;
  HANDLE_ERROR ( cudaSetDevice ( deviceId ) );
  HANDLE_ERROR ( cudaGLSetGLDevice ( deviceId ) );

  int width = 300;
  int height = width;

  RipplingImageCudaMOO rippling ( width, height, 0, 0.5 );
  RayTracingImageCudaMOO rayTracing ( width, height, 0, 0.005, 20 );
  Mandelbrot mandel ( width, height, DomaineMaths ( -2.1f, -1.3f, 0.8f, 1.3f ), 80 );
  Julia julia ( width, height, DomaineMaths ( -1.3f, -1.4f, 1.3f, 1.4f ), 80, -0.12f, 0.85f );
  HeaterImageCuda heater ( width, height, 0.1f, 1 );

  ImageCudaViewers imageViewerRippling ( &rippling, true, false, 0, 0 );
  ImageCudaViewers imageViewerRayTracing ( &rayTracing, true, false, width, 0 );
  ImageCudaViewers imageViewerMandelbrot ( &mandel, true, true, 0, width + 50 );
  ImageCudaViewers imageViewerJulia ( &julia, true, true, width, width + 50 );
  ImageCudaViewers imageViewerHeater ( &heater, true, false, 2*width, 0 );

  ImageCudaViewers::runALL ();

  return true;

}

bool useRippling ( void ) {
  int deviceId = 0;
  HANDLE_ERROR ( cudaSetDevice ( deviceId ) );
  HANDLE_ERROR ( cudaGLSetGLDevice ( deviceId ) );

  RipplingImageCudaMOO rippling ( 500, 500, 0, 0.5 );
  ImageCudaViewers imageViewerRippling ( &rippling, true, false, 0, 0 );

  ImageCudaViewers::runALL ();
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

bool useMandelbrot ( void ) {
  int deviceId = 0;
  HANDLE_ERROR ( cudaSetDevice ( deviceId ) );
  HANDLE_ERROR ( cudaGLSetGLDevice ( deviceId ) );
  float x0 = -2.1f;
  float x1 = 0.8f;
  float y0 = -1.3f;
  float y1 = 1.3f;

  Mandelbrot mandel ( 1200, 700, DomaineMaths ( x0, y0, x1, y1 ), 80 );
  ImageCudaViewers viewer ( &mandel );
  ImageCudaViewers::runALL ();
  return true;
}

bool useJulia ( void ) {
  int deviceId = 0;
  HANDLE_ERROR ( cudaSetDevice ( deviceId ) );
  HANDLE_ERROR ( cudaGLSetGLDevice ( deviceId ) );
  float x0 = -1.3f;
  float x1 = 1.3f;
  float y0 = -1.4f;
  float y1 = 1.4f;

  Julia julia ( 800, 600, DomaineMaths ( x0, y0, x1, y1 ), 52, -0.12f, 0.85f );
  ImageCudaViewers viewer ( &julia );
  ImageCudaViewers::runALL ();
  return true;
}

bool useHeater ( void ) {
  int deviceId = 0;
  HANDLE_ERROR ( cudaSetDevice ( deviceId ) );
  HANDLE_ERROR ( cudaGLSetGLDevice ( deviceId ) );

  HeaterImageCuda heater ( 800, 800, 0.1f, 1 );
  ImageCudaViewers viewer ( &heater );
  ImageCudaViewers::runALL ();
  return true;
}
