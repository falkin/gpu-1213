#include "KernelFilterImageCudaViewer.h"
#include <string.h>
#include <opencv2/opencv.hpp>
#include "cuda_runtime.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

extern void initKernelFillImage( const unsigned int w, const unsigned int h );
extern void launchKernelFillImageKernel ( uchar4* ptrDevImageGL, const uchar4* ptrCudaImage, const unsigned int w, const unsigned int h );
/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
KernelFilterImageCudaViewer::KernelFilterImageCudaViewer ( unsigned int w, unsigned int h, const std::string filename )
    : ImageCudaMOOs_A ( w, h ), _capture ( filename, std::string ( "Kernel" ) ) {
  initKernelFillImage( w, h );
  std::cout << "Constructed KernelFilterImageCudaViewer" << std::endl;
  _capture.printInfo ();
}

void KernelFilterImageCudaViewer::animationStep ( bool& isNeedUpdateView ) {
  isNeedUpdateView = true;
}
/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void KernelFilterImageCudaViewer::fillImageGL ( uchar4* ptrDevImageGL, int w, int h ) {
  cv::Mat img = _capture.capturer ();
  uchar4* ptrCudaImage = _capture.castToUChar4(&img);
  launchKernelFillImageKernel(ptrDevImageGL, ptrCudaImage, w, h);
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

