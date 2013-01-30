#ifndef MOUSEEVENTIMAGEVIEWERS_H_
#define MOUSEEVENTIMAGEVIEWERS_H_

#include <ImageViewers.h>

class HeaterMOO;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MouseEventImageViewers: public ImageViewers {
public:
  MouseEventImageViewers ( ImageMOOs* ptrImageMOO, bool useAnimation = false, bool useSelection = false, int pxFrame = 0, int pyFrame = 0 );
  virtual ~MouseEventImageViewers ();
private:
  void mousePressedPerformed ( int button, int state, int x, int y );
  HeaterMOO* _heaterMOO;
};

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
