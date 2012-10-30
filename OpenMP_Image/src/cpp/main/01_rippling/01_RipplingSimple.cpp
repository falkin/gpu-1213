#include "01_RipplingSimple.h"
#include <math.h>

RipplingSimple::RipplingSimple ( Point m, Point n, Time dt )
    : ImageMOOs ( m, n ) {
}

Color RipplingSimple::ComputeColor ( Point x, Point y, Dim dim, Time time ) {
  double midDim = dim / 2.0;
  double fx = x - midDim;
  double fy = y - midDim;
  return 0;
}

void RipplingSimple::animationStep ( bool& isNeedUpdateView ) {

}
