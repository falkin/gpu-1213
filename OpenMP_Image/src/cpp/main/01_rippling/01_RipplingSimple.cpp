#include "01_RipplingSimple.h"
#include <math.h>

RipplingSimple::RipplingSimple ( Point m, Time dt ):
ImageMOOs( m, n );

void RipplingSimple::Ripple ( Time time ) {

}

Color RipplingSimple::ComputeColor( Point x, Point y, Dim dim, Time time ) {
	double midDim = dim / 2.0;
	double fx = x - midDim;
	double fy = y - midDim;
}

void RipplingSimple::animationStep( bool& isNeedUpdateView ) {

}
