#ifndef HEATERIMAGECUDA_H_
#define HEATERIMAGECUDA_H_

#include "ImageCudaMOOs_A.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class HeaterImageCuda: public ImageCudaMOOs_A {
public:
  HeaterImageCuda ( unsigned int w, unsigned int h, float tsStart = 0, float dt = 1 );
  virtual ~HeaterImageCuda ();
  void animationStep ( bool& isNeedUpdateView );

private:
  void fillImageGL ( uchar4* ptrDevImageGL, int w, int h );
};

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
