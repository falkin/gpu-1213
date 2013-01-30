#include "KernelFilterImageCudaViewer.h"
#include <string.h>
#include <opencv2/opencv.hpp>
#include "cuda_runtime.h"
#include "KernelFilterImpl.h"

extern void initKernelFillImage ( const uint32_t w, const uint32_t h, const float* kernel, const size_t kernelSize );
extern double launchKernelFillImageKernel ( uchar4* ptrDevImageGL, const uchar4* ptrCudaImage, const unsigned int w, const unsigned int h,
    const KernelKind kind, const GrayscaleMethod grayscale, const dim3 dg, const dim3 db );

/**
 *
 */
KernelFilterImageCudaViewer::KernelFilterImageCudaViewer ( const uint32_t w, const uint32_t h, const std::string filename,
    const float* kernel, const size_t kernelSize, const KernelKind kind, const GrayscaleMethod grayscale, const dim3 dg, const dim3 db )
    : ImageCudaMOOs_A ( w, h ), _capture ( filename, std::string ( "Kernel CUDA" ) ), _kernel ( kernel ), _kernelSize ( kernelSize ), _kind (
        kind ), _method ( grayscale ), _dg ( dg ), _db ( db ) {
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
  launchKernelFillImageKernel ( ptrDevImageGL, ptrCudaImage, w, h, _kind, _method, _dg, _db );
}

double KernelFilterImageCudaViewer::fillImageGL ( uchar4* ptrDevImageGL, int w, int h, const KernelKind kind, const GrayscaleMethod method, const dim3 dg, const dim3 db ) {
  cv::Mat img = _capture.capturer ();
  uchar4* ptrCudaImage = _capture.castToUChar4 ( &img );
  return launchKernelFillImageKernel ( ptrDevImageGL, ptrCudaImage, w, h, kind, method, dg, db );
}
