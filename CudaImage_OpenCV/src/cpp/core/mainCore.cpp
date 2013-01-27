#include <iostream>
#include <stdlib.h>
#include "limits.h"
#include "Device.h"
#include "cudaTools.h"
#include "KernelFilterImageCudaViewer.h"
#include "ImageCudaViewers.h"

using std::cout;
using std::endl;

int mainCore ();

static bool useKernelFilter ( void );

/**
 *
 */
int mainCore () {
  bool isOk = true;
  isOk &= useKernelFilter ();

  cout << "\nisOK = " << isOk << endl;
  cout << "\nEnd : mainCore" << endl;

  return isOk ? EXIT_SUCCESS : EXIT_FAILURE;
}

/**
 *
 */
void createKernel ( float** kernel, size_t* size ) {
  size_t tabSize = 81;
  float tab[81] = { 0.0828, 0.1987, 0.3705, 0.5366, 0.6063, 0.5366, 0.3705, 0.1987, 0.0828, 0.1987, 0.4746, 0.8646, 1.1794, 1.2765, 1.1794,
      0.8646, 0.4746, 0.1987, 0.3705, 0.8646, 1.3475, 1.0033, 0.4061, 1.0033, 1.3475, 0.8646, 0.3705, 0.5366, 1.1794, 1.0033, -2.8306,
      -6.4829, -2.8306, 1.0033, 1.1794, 0.5366, 0.6063, 1.2765, 0.4061, -6.4829, -12.7462, -6.4829, 0.4061, 1.2765, 0.6063, 0.5366, 1.1794,
      1.0033, -2.8306, -6.4829, -2.8306, 1.0033, 1.1794, 0.5366, 0.3705, 0.8646, 1.3475, 1.0033, 0.4061, 1.0033, 1.3475, 0.8646, 0.3705,
      0.1987, 0.4746, 0.8646, 1.1794, 1.2765, 1.1794, 0.8646, 0.4746, 0.1987, 0.0828, 0.1987, 0.3705, 0.5366, 0.6063, 0.5366, 0.3705,
      0.1987, 0.0828 };
  float* newTab = (float*) malloc ( tabSize * sizeof(float) );
  for ( size_t i = 0; i < tabSize; i++ ) {
    newTab[i] = tab[i] / 100.0f;

  }
  *kernel = newTab;
  *size = tabSize;
}

/**
 *
 */
bool useKernelFilter ( void ) {
  int deviceId = 0;
  HANDLE_ERROR( cudaSetDevice ( deviceId ) );
  HANDLE_ERROR( cudaGLSetGLDevice ( deviceId ) );
  float* kernelEdge;
  size_t kernelSize;
  createKernel ( &kernelEdge, &kernelSize );
  KernelFilterImageCudaViewer kernel ( 1920, 1080, std::string ( "/home/studentmse9/hearc/cuda/data/nasaFHD.avi" ), kernelEdge,
      kernelSize );
  ImageCudaViewers viewer ( &kernel );
  ImageCudaViewers::runALL ();
  return true;
}
