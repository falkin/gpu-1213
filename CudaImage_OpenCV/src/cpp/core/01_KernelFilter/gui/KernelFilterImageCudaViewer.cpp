#include "KernelFilterImageCudaViewer.h"
#include <string.h>
#include <opencv2/opencv.hpp>
#include "cuda_runtime.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

extern void launchKernelFillImageKernel ( uchar4* ptrDevImageGL, uchar4* ptrCudaImage, int w, int h );
/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
KernelFilterImageCudaViewer::KernelFilterImageCudaViewer ( unsigned int w, unsigned int h, const std::string filename )
    : ImageCudaMOOs_A ( w, h ), _capture ( filename, std::string ( "Kernel" ) ) {
  std::cout << "Constructed KernelFilterImageCudaViewer" << std::endl;
  _capture.printInfo ();
}

void KernelFilterImageCudaViewer::animationStep ( bool& isNeedUpdateView ) {
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

