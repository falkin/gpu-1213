#ifndef KERNELFILTERIMAGECUDAVIEWER_H_
#define KERNELFILTERIMAGECUDAVIEWER_H_
#include "ImageCudaMOOs_A.h"
#include "CaptureVideo.h"

class KernelFilterImageCudaViewer: public ImageCudaMOOs_A {
public:
  KernelFilterImageCudaViewer ( const uint32_t w, const uint32_t h, const std::string filename, const float* kernel,
      const size_t kernelSize );
  virtual ~KernelFilterImageCudaViewer () {
  }
  void animationStep ( bool& isNeedUpdateView );
private:
  void fillImageGL ( uchar4* ptrDevImageGL, int w, int h );
  std::string _filename;
  CaptureVideo _capture;
  const float* _kernel;
  size_t _kernelSize;
};

#endif
