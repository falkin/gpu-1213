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
using std::cout;
using std::endl;

int mainCore ( void );

static bool useRippling ( void );
static bool useRayTracing ( void );
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
  //isOk &= useMandelbrot ();
  //isOk &= useJulia ();
  isOk &= useHeater ();
  //isOk &= demoAll ();

  cout << "\n-------------------------------------------------" << endl;
  cout << "End Main : isOk = " << isOk << endl;

  return isOk ? EXIT_SUCCESS : EXIT_FAILURE;
}

/*--------------------------------------*\
 |*     Private         *|
 \*-------------------------------------*/

bool demoAll ( void ) {
  int deviceId = 0;
  HANDLE_ERROR ( cudaSetDevice ( deviceId ) );
  HANDLE_ERROR ( cudaGLSetGLDevice ( deviceId ) );

  int width = 300;
  int height = width;

  RipplingImageCudaMOO rippling ( width, height, 0, 0.5 );
  RayTracingImageCudaMOO rayTracing ( width, height, 0, 0.005, 20 );

  ImageCudaViewers imageViewerRippling ( &rippling, true, false, 0, 0 );
  ImageCudaViewers imageViewerRayTracing ( &rayTracing, true, false, width, 0 );

  ImageCudaViewers::runALL ();

  return true;

}

bool useRippling ( void ) {
  int deviceId = 0;
  HANDLE_ERROR ( cudaSetDevice ( deviceId ) );
  HANDLE_ERROR ( cudaGLSetGLDevice ( deviceId ) );
  RipplingImageCudaMOO ripplingA ( 600, 600, 0, 0.5 );

  bool isAnimationEnable = true;
  ImageCudaViewers imageViewer ( &ripplingA, isAnimationEnable );
  ImageCudaViewers::runALL ();

  return true;
}

bool useRayTracing ( void ) {
  int deviceId = 0;
  HANDLE_ERROR ( cudaSetDevice ( deviceId ) );
  HANDLE_ERROR ( cudaGLSetGLDevice ( deviceId ) );
  RayTracingImageCudaMOO image ( 600, 600, 0, 0.005, 20 );

  bool isAnimationEnable = true;
  ImageCudaViewers imageViewer ( &image, isAnimationEnable );
  ImageCudaViewers::runALL ();

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
