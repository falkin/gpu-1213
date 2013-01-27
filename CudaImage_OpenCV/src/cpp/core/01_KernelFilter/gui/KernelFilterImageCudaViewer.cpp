#include "KernelFilterImageCudaViewer.h"
#include <string.h>
#include <opencv2/opencv.hpp>
#include "cuda_runtime.h"

extern void initKernelFillImage ( const uint32_t w, const uint32_t h, const float* kernel, const size_t kernelSize );
extern void launchKernelFillImageKernel ( uchar4* ptrDevImageGL, const uchar4* ptrCudaImage, const unsigned int w, const unsigned int h );

/**
 *
 */
KernelFilterImageCudaViewer::KernelFilterImageCudaViewer ( const uint32_t w, const uint32_t h, const std::string filename,
    const float* kernel, const size_t kernelSize )
    : ImageCudaMOOs_A ( w, h ), _capture ( filename, std::string ( "Kernel" ) ), _kernel ( kernel ), _kernelSize( kernelSize ) {
  std::cout << "Constructed KernelFilterImageCudaViewer" << std::endl;
  _capture.printInfo ();
  initKernelFillImage ( w, h, _kernel, _kernelSize );
}

/**
 *
 */
void KernelFilterImageCudaViewer::animationStep ( bool& isNeedUpdateView ) {
  isNeedUpdateView = true;
}

/**
 *
 */
void KernelFilterImageCudaViewer::fillImageGL ( uchar4* ptrDevImageGL, int w, int h ) {
  cv::Mat img = _capture.capturer ();
  uchar4* ptrCudaImage = _capture.castToUChar4 ( &img );
  launchKernelFillImageKernel ( ptrDevImageGL, ptrCudaImage, w, h );
}
