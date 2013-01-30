#include <iostream>
#include <stdlib.h>
#include "limits.h"
#include "Device.h"
#include "cudaTools.h"
#include "KernelFilterImageCudaViewer.h"
#include "KernelFilterCPPMOO.h"
#include "ImageCudaViewers.h"
#include "ImageViewers.h"
#include "PinnedVSUnpinned.h"
#include "KernelFilterImpl.h"

#define PINNED_VS_UNPINNED 10

using std::cout;
using std::endl;

int mainCore ();

static bool useKernelFilterCUDA ( void );
static bool useKernelFilterCUDABenchmarks ( void );
static bool useKernelFilterCPP ( void );
static bool usePinnedVSUnpinned ( void );
static bool usePinnedVSUnpinnedVariable ( void );

/**
 *
 */
int mainCore () {
  bool isOk = true;
  isOk &= useKernelFilterCUDA ();
  //isOk &= useKernelFilterCUDABenchmarks ();
  //isOk &= useKernelFilterCPP ();
  //isOk &= usePinnedVSUnpinned ();
  //isOk &= usePinnedVSUnpinnedVariable ();

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
bool useKernelFilterCUDA ( void ) {
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

bool useKernelFilterCUDABenchmarks ( void ) {
  int deviceId = 4;
  HANDLE_ERROR( cudaSetDevice ( deviceId ) );
  HANDLE_ERROR( cudaGLSetGLDevice ( deviceId ) );
  uchar4* ptrDevImageGL;
  HANDLE_ERROR( cudaMalloc((void**) &ptrDevImageGL, 1920 * 1080 * sizeof(uchar4)) );
  HANDLE_ERROR( cudaMemset(ptrDevImageGL, 0, 1920 * 1080 * sizeof(uchar4)) );
  float* kernelEdge;
  size_t kernelSize;
  createKernel ( &kernelEdge, &kernelSize );
  // texture global
  KernelFilterImageCudaViewer kernel ( 1920, 1080, std::string ( "/home/studentmse9/hearc/cuda/data/nasaFHD.avi" ), kernelEdge,
      kernelSize );
  cout << "TEX_GLOBAL - AVERAGE" << endl;
  dim3 dg;
  dim3 db ( 8, 8, 1 );
  uint32_t power;
  for ( uint32_t exp = 4; exp < 13; exp++ ) {
    power = pow ( 2, exp );
    dg = dim3 ( power, power, 1 );
    cout << "dg: " << power << endl;
    for ( size_t itr = 0; itr < 10; itr++ ) {
      cout << kernel.fillImageGL ( ptrDevImageGL, 1920, 1080, TEXTURE_GLOBAL, AVERAGE, dg, db ) << endl;
    }
  }
  dg = dim3 ( 32, 32, 1 );
  for ( uint32_t exp = 3; exp <= 10; exp++ ) {
    power = pow ( 2, exp );
    db = dim3 ( power, power, 1 );
    cout << "db: " << power << endl;
    for ( size_t itr = 0; itr < 10; itr++ ) {
      cout << kernel.fillImageGL ( ptrDevImageGL, 1920, 1080, TEXTURE_GLOBAL, AVERAGE, dg, db ) << endl;
    }
  }

  cout << "TEX_CONSTANT - AVERAGE" << endl;
  db = ( 8, 8, 1 );
  for ( uint32_t exp = 4; exp < 13; exp++ ) {
    power = pow ( 2, exp );
    dg = dim3 ( power, power, 1 );
    cout << "dg: " << power << endl;
    for ( size_t itr = 0; itr < 10; itr++ ) {
      cout << kernel.fillImageGL ( ptrDevImageGL, 1920, 1080, TEXTURE_CONSTANT, AVERAGE, dg, db ) << endl;
    }
  }
  dg = dim3 ( 32, 32, 1 );
  for ( uint32_t exp = 3; exp <= 10; exp++ ) {
    power = pow ( 2, exp );
    db = dim3 ( power, power, 1 );
    cout << "db: " << power << endl;
    for ( size_t itr = 0; itr < 10; itr++ ) {
      cout << kernel.fillImageGL ( ptrDevImageGL, 1920, 1080, TEXTURE_CONSTANT, AVERAGE, dg, db ) << endl;
    }
  }

  cout << "TEX_CONSTANT MUL - AVERAGE" << endl;
  db = dim3 ( 8, 8, 1 );
  for ( uint32_t exp = 4; exp < 13; exp++ ) {
    power = pow ( 2, exp );
    dg = dim3 ( power, power, 1 );
    cout << "dg: " << power << endl;
    for ( size_t itr = 0; itr < 10; itr++ ) {
      cout << kernel.fillImageGL ( ptrDevImageGL, 1920, 1080, TEXTURE_CONSTANT_MUL24, AVERAGE, dg, db ) << endl;
    }
  }
  dg = dim3 ( 32, 32, 1 );
  for ( uint32_t exp = 3; exp <= 10; exp++ ) {
    power = pow ( 2, exp );
    db = dim3 ( power, power, 1 );
    cout << "db: " << power << endl;
    for ( size_t itr = 0; itr < 10; itr++ ) {
      cout << kernel.fillImageGL ( ptrDevImageGL, 1920, 1080, TEXTURE_CONSTANT_MUL24, AVERAGE, dg, db ) << endl;
    }
  }
  return true;
}

/**
 *
 */
bool useKernelFilterCPP ( void ) {
  float* kernelEdge;
  size_t kernelSize;
  createKernel ( &kernelEdge, &kernelSize );
  KernelFilterCPPMOO kernel ( 1920, 1080, std::string ( "/home/studentmse9/hearc/cuda/data/nasaFHD.avi" ), kernelEdge, kernelSize, true );
  ImageViewers viewer ( &kernel, true );
  ImageViewers::runALL ();
  return true;
}

/**
 *
 */
bool usePinnedVSUnpinned ( void ) {
  int deviceId = 0;
  HANDLE_ERROR( cudaSetDevice ( deviceId ) );
  HANDLE_ERROR( cudaGLSetGLDevice ( deviceId ) );
  std::string file ( "/home/studentmse9/hearc/cuda/data/nasaFHD.avi" );
  PinnedVSUnpinned pinned ( 1920, 1080, file, PINNED );
  cout << "Pinned:" << endl;
  for ( size_t i = 0; i < PINNED_VS_UNPINNED; i++ ) {
    cout << pinned.transfert () << endl;
  }
  cout << endl << "Unpinned:" << endl;
  PinnedVSUnpinned unpinned ( 1920, 1080, file, UNPINNED );
  for ( size_t i = 0; i < PINNED_VS_UNPINNED; i++ ) {
    cout << unpinned.transfert () << endl;
  }
  return true;
}

bool usePinnedVSUnpinnedVariable ( void ) {
  int deviceId = 0;
  HANDLE_ERROR( cudaSetDevice ( deviceId ) );
  HANDLE_ERROR( cudaGLSetGLDevice ( deviceId ) );

  double* ptr = 0;
  double* ptrDMA = 0;

  for ( size_t exp = pow ( 2, 13 ); exp < pow ( 2, 15 ); exp += 1000 ) {
    // malloc
    size_t size = exp * exp * sizeof(double);
    ptr = (double*) malloc ( size );
    HANDLE_ERROR( cudaHostAlloc ( (void**) &ptrDMA, size, cudaHostAllocDefault ) );
    memset ( ptr, 0, size );
    memset ( ptrDMA, 0, size );
    cout << "Pinned " << exp << endl;
    for ( size_t i = 0; i < PINNED_VS_UNPINNED; i++ ) {
      cout << PinnedVSUnpinned::transfert ( ptrDMA, size ) << endl;
    }
    cout << "Unpinned " << exp << endl;
    for ( size_t i = 0; i < PINNED_VS_UNPINNED; i++ ) {
      cout << PinnedVSUnpinned::transfert ( ptr, size ) << endl;
    }
    free ( ptr );
    cudaFreeHost ( ptrDMA );
    // free
  }

  return true;
}
