#ifndef KERNELFILERCPPMOO_H_
#define KERNELFILERCPPMOO_H_

#include "ImageMOOs.h"
#include "CaptureVideo.h"
#include <opencv2/opencv.hpp>

class KernelFilterCPPMOO: public ImageMOOs {
public:
  KernelFilterCPPMOO ( const uint32_t w, const uint32_t h, const std::string filename, float* kernel, const size_t kernelSize, const bool omp = false );
  virtual ~KernelFilterCPPMOO () {
  }
  void animationStep ( bool& isNeedUpdateView );
private:
  void fillImage ( const uchar4* img, const uint32_t w, const uint32_t h );
  std::string _filename;
  CaptureVideo _capture;
  cv::Mat _kernelMat;
  bool _omp;
};

#endif
