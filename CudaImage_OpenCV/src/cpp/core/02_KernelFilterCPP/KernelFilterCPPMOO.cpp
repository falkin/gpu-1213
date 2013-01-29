#include "KernelFilterCPPMOO.h"
#include <stdint.h>

/**
 *
 */
KernelFilterCPPMOO::KernelFilterCPPMOO ( const uint32_t w, const uint32_t h, const std::string filename, float* kernel,
    const size_t kernelSize, const bool omp )
    : ImageMOOs ( w, h ), _filename ( filename ), _capture ( _filename, std::string ( "Kernel C++/OpenCV" ) ), _kernelMat (
        cv::Mat ( sqrt ( kernelSize ), sqrt ( kernelSize ), CV_32FC1, kernel ) ), _omp ( omp ) {
}

/**
 *
 */
void KernelFilterCPPMOO::animationStep ( bool& isNeedUpdateView ) {
  isNeedUpdateView = true;
  cv::Mat img = _capture.capturer ();
  cv::Mat conv;
  // when ddepth=-1, the output image will have the same depth as the source.
  // anchor of the kernel that indicates the relative position of a filtered point within the kernel;
  // the anchor should lie within the kernel; default value (-1,-1) means that the anchor is at the kernel center.
  //cv::filter2D(src, dst, ddepth, kernel, anchor, delta, bordertype);
  cv::filter2D ( img, conv, -1, _kernelMat );
  fillImage ( Capture_A::castToUChar4 ( &conv ), conv.rows, conv.cols );
}

/**
 *
 */
void KernelFilterCPPMOO::fillImage ( const uchar4* img, const uint32_t w, const uint32_t h ) {
#pragma omp parallel for if ( _omp )
  for ( uint32_t i = 1; i < w; i++ ) {
    for ( uint32_t j = 1; j < h; j++ ) {
      uint32_t pos = indice1D ( i, j ) / 4;
      setRGBA ( i, j, img[pos].x + 64, img[pos].y + 64, img[pos].z + 64, 255 );
    }
  }
}
