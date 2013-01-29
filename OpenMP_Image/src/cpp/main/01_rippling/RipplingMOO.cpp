#include "RipplingMOO.h"
#include <math.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

RipplingMOO::RipplingMOO(unsigned int w, unsigned int h, float tStart, float dt, const bool omp) :
	ImageMOOs(w, h), _omp ( omp )
    {
    this->t = tStart;
    this->dt = dt;
    fillImage(tStart);
    }

RipplingMOO::~RipplingMOO()
    {

    }
void RipplingMOO::animationStep(bool& isNeedUpdateView)
    {
    t += dt;
    fillImage(t);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void RipplingMOO::fillImage(float t)
    {
    int h = getH();
    int w = getW();
    
#pragma omp parallel for if ( _omp )
    for (int i = 1; i <= h; i++)
	{
	for (int j = 1; j <= w; j++)
	    {
	    setPixel(i, j, t);
	    }
	}
    }

void RipplingMOO::setPixel(int i, int j, float t)
    {
    unsigned char r, g, b;
    r = g = b = computeColor(i, j, t, getW(), getH());
    setRGBA(i, j, r, g, b);
    }

unsigned char RipplingMOO::computeColor(int x, int y, float t, int w, int h)
    {
    float fx = x - w / 2.;
    float fy = y - h / 2.;

    float d = sqrt(fx * fx + fy * fy);

    return 128 + 127 * (cos((d / 10.) - (t / 7)) / ((d / 10) + 1));

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

