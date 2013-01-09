#include <iostream>
#include <stdlib.h>
#include "limits.h"
#include "Device.h"
#include "cudaTools.h"
#include "KernelFilterImageCudaViewer.h"
#include "ImageCudaViewers.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*     Declaration           *|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*   Imported    *|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*   Public      *|
 \*-------------------------------------*/

int mainCore ();

/*--------------------------------------*\
 |*   Private     *|
 \*-------------------------------------*/

static bool useKernelFilter ( void );

/*----------------------------------------------------------------------*\
 |*     Implementation          *|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*   Public      *|
 \*-------------------------------------*/

int mainCore () {
  //Device::print(deviceId, "Execute on device : ");

  bool isOk = true;
  //isOk &= useHello();
  //isOk &= useReduction();
  isOk &= useKernelFilter ();

  cout << "\nisOK = " << isOk << endl;
  cout << "\nEnd : mainCore" << endl;

  return isOk ? EXIT_SUCCESS : EXIT_FAILURE;
}

/*--------------------------------------*\
 |*   Private     *|
 \*-------------------------------------*/

bool useKernelFilter ( void ) {
  int deviceId = 0;
  HANDLE_ERROR( cudaSetDevice ( deviceId ) );
  HANDLE_ERROR( cudaGLSetGLDevice ( deviceId ) );
  cout << "Running Kernel labwork !" << endl;
  KernelFilterImageCudaViewer kernel ( 1920, 1080, std::string ( "/home/studentmse9/hearc/cuda/data/nasaFHD.avi" ) );
  ImageCudaViewers viewer ( &kernel );
  ImageCudaViewers::runALL ();
  return true;
}

/*----------------------------------------------------------------------*\
 |*     End           *|
 \*---------------------------------------------------------------------*/

