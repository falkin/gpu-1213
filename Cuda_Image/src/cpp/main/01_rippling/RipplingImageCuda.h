#ifndef RIPPLINIMAGECUDA_H
#define RIPPLINIMAGECUDA_H

#include "ImageCudaMOOs_A.h"

class RipplingImageCudaMOO: public ImageCudaMOOs_A {
public:
  RipplingImageCudaMOO ( unsigned int w, unsigned int h, float tsStart = 0, float dt = 1 );
  virtual ~RipplingImageCudaMOO ();
  void animationStep ( bool& isNeedUpdateView );

private:
  void fillImageGL ( uchar4* ptrDevImageGL, int w, int h );
  void setPixel ( int i, int j, float t );
  unsigned char computeColor ( int i, int j, float t, int w, int h );

  float t;
  float dt;
};

#endif
