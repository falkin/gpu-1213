#include "MouseEventImageViewers.h"
#include "HeaterMOO.h"
#include <iostream>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

MouseEventImageViewers::MouseEventImageViewers ( ImageMOOs* ptrImageMOO, bool useAnimation )
    : ImageViewers ( ptrImageMOO, useAnimation ), _heaterMOO ( (HeaterMOO*) ptrImageMOO ) {
}

MouseEventImageViewers::~MouseEventImageViewers () {
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/
void MouseEventImageViewers::mousePressedPerformed ( int button, int state, int x, int y ) {
  if ( state == 1 && ( button == 0 || button == 2 ) ) {
    _heaterMOO->addHeater ( x, y, button == 0 ? HEATER : COOLER );
  }
  std::cout << "Button: [" << button << "], state: [" << state << "], (x=" << x << ", y=" << y << ")" << std::endl;
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

