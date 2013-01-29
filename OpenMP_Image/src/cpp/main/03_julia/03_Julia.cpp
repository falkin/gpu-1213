#include "03_Julia.h"

Julia::Julia ( const Dim w, const Dim h, const DomaineMaths& domaine, const int n, const float real_c, const float img_c, const bool omp )
    : ImageFonctionelMOOs_A ( w, h, domaine ), n ( n ), real_c ( real_c ), img_c ( img_c ), _omp ( omp ) {
  fillImage ( domaine );
}

void Julia::fillImage ( const DomaineMaths& domaine ) {
  Dim h = getH ();
  Dim w = getW ();
#pragma omp parallel for if ( _omp )
  for ( int i = 1; i <= h; i++ ) {
    for ( int j = 1; j <= w; j++ ) {
      setPixel ( i, j, domaine );
    }
  }
}

void Julia::setPixel ( const Point i, const Point j, const DomaineMaths& domaine ) {

  float x0 = 0.;
  float y0 = 0.;

  toXY ( i, j, x0, y0 );

  float x = x0;
  float y = y0;
  float xtemp = 0;
  int itr = 0;

  while ( itr < n && ( x * x + y * y ) < 4 ) {
    xtemp = ( x * x - y * y ) + real_c;
    y = ( 2 * x * y ) + img_c;
    x = xtemp;
    itr++;
  }
  if ( itr == n && ( x * x + y * y ) < 4 ) {
    setFloatRGBA ( i, j, 0, 0, 0 );
  } else {
    setHue ( i, j, ( (float) ( itr - 1 ) ) / n );
  }
}
