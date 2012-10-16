#ifndef 01_RIPPLINGSIMPLE_H_
#define 01_RIPPLINGSIMPLE_H_

#include "ImageMOOs.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

typedef unsigned char Color;
typedef float Time;
typedef unsigned int Dim;
typedef unsigned int Point;

class RipplingSimple : public ImageMOOs {
public:
	RipplingSimple( Point m, Point n );
	virtual ~RipplingSimple();
	void Ripple( Time time );
	void animationStep( bool& isNeedUpdateView );

private:
	Color ComputeColor( Point x, Point y, Dim dim, Time time );
};

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
