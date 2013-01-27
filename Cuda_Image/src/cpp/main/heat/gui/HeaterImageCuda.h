#ifndef HEATERIMAGECUDA_H_
#define HEATERIMAGECUDA_H_

#include "ImageCudaMOOs_A.h"

class HeaterImageCuda: public ImageCudaMOOs_A {
public:
  HeaterImageCuda ( const uint32_t w, const uint32_t h, const float k, const uint32_t blindItr );
  virtual ~HeaterImageCuda ();
  void animationStep ( bool& isNeedUpdateView );

private:
  void fillImageGL ( uchar4* ptrDevImageGL, int w, int h );

  float _k;
  uint32_t _blindItr;
};

#endif 
