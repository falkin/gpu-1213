#include "RipplingImageCuda.h"
#include <math.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
extern void launchKernelFillImage ( uchar4* ptrDevImageGL, int w, int h, float t );
/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

RipplingImageCudaMOO::RipplingImageCudaMOO ( unsigned int w, unsigned int h, float tStart, float dt )
    : ImageCudaMOOs_A ( w, h ), t ( tStart ), dt ( dt ) {
}

RipplingImageCudaMOO::~RipplingImageCudaMOO () {
}

void RipplingImageCudaMOO::animationStep ( bool& isNeedUpdateView ) {
  t += dt;
  isNeedUpdateView = true;
  //fillImage ( t );
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void RipplingImageCudaMOO::fillImageGL ( uchar4* ptrDevImageGL, int w, int h ) {
  launchKernelFillImage ( ptrDevImageGL, w, h, t );
}

//void RipplingImageCudaMOO::setPixel ( int i, int j, float t ) {
//  unsigned char r, g, b;
//  r = g = b = computeColor ( i, j, t, getW (), getH () );
//  setRGBA ( i, j, r, g, b );
//}
//
//unsigned char RipplingImageCudaMOO::computeColor ( int x, int y, float t, int w, int h ) {
//  float fx = x - w / 2.;
//  float fy = y - h / 2.;
//
//  float d = sqrt ( fx * fx + fy * fy );
//
//  return 128 + 127 * ( cos ( ( d / 10. ) - ( t / 7 ) ) / ( ( d / 10 ) + 1 ) );
//}
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

