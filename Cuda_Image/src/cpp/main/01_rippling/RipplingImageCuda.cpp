#include "RipplingImageCuda.h"
#include <math.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
extern void launchKernelFillImageRippling ( uchar4* ptrDevImageGL, int w, int h, float t );
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
  launchKernelFillImageRippling ( ptrDevImageGL, w, h, t );
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

