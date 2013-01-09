#include "ImageCuda.h"
#include <math.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
extern void launchKernelFillImageRay ( uchar4* ptrDevImageGL, int w, int h, float t );
/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

ImageCudaMOO::ImageCudaMOO ( unsigned int w, unsigned int h, float tStart, float dt )
    : ImageCudaMOOs_A ( w, h ), t ( tStart ), dt ( dt ) {
}

ImageCudaMOO::~ImageCudaMOO () {

}

void ImageCudaMOO::animationStep ( bool& isNeedUpdateView ) {
  t += dt;
  isNeedUpdateView = true;
  //fillImage ( t );
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void ImageCudaMOO::fillImageGL ( uchar4* ptrDevImageGL, int w, int h ) {
  launchKernelFillImageRay ( ptrDevImageGL, w, h, t );
}


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

