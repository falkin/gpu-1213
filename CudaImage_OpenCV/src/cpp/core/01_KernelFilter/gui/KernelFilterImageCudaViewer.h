#ifndef KERNELFILTERIMAGECUDAVIEWER_H_
#define KERNELFILTERIMAGECUDAVIEWER_H_
#include "ImageCudaMOOs_A.h"
#include "CaptureVideoDMA.h"
#include "KernelFilterImpl.h"

class KernelFilterImageCudaViewer: public ImageCudaMOOs_A {
public:
  KernelFilterImageCudaViewer ( const uint32_t w, const uint32_t h, const std::string filename, const float* kernel,
      const size_t kernelSize, const KernelKind kind = TEXTURE_CONSTANT_MUL24, const GrayscaleMethod grayscale = AVERAGE, const dim3 dg =
          dim3 ( 8, 8, 1 ), const dim3 db = dim3 ( 32, 32, 1 ) );
  virtual ~KernelFilterImageCudaViewer () {
  }
  void animationStep ( bool& isNeedUpdateView );

  double fillImageGL ( uchar4* ptrDevImageGL, int w, int h, const KernelKind kind, const GrayscaleMethod method, const dim3 dg, const dim3 db );
private:
  void fillImageGL ( uchar4* ptrDevImageGL, int w, int h );
  std::string _filename;
  CaptureVideoDMA _capture;
  const float* _kernel;
  size_t _kernelSize;
  KernelKind _kind;
  GrayscaleMethod _method;
  dim3 _dg;
  dim3 _db;
};

#endif
