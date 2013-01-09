#include "ImageViever.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

ImageViever::ImageViever ( const string& titleFrame )
    : chrono () {
  this->titleFrame = titleFrame;
  //namedWindow(idWindow, 1);
  compteur = 0;
}

ImageViever::~ImageViever ( void ) {
  // rien
}

void ImageViever::show ( Mat* ptrMatCapture ) {
  imshow ( titleFrame, *ptrMatCapture );
  compteur++;
}

int ImageViever::fps ( void ) {
  double delayS = chrono.timeFlight ();
  int fps = compteur / delayS;

  if ( delayS > 2.0 ) //disons
      {
    compteur = 0;
    chrono.start ();
  }

  return fps;
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

