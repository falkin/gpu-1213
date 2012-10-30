#include "02_Mandelbrot.h"

Mandelbrot::Mandelbrot ( const Dim w, const Dim h, const DomaineMaths& domaine, const int n )
    : ImageFonctionelMOOs_A ( w, h, domaine ), n ( n ) {
  fillImage ( domaine );
}

void Mandelbrot::fillImage ( const DomaineMaths& domaine ) {
  Dim h = getH ();
  Dim w = getW ();
  for ( int i = 1; i <= h; i++ ) {
    for ( int j = 1; j <= w; j++ ) {
      setPixel ( i, j, domaine );
    }
  }
}

void Mandelbrot::setPixel ( const Point i, const Point j, const DomaineMaths& domaine ) {
  double distX = domaine.x0 + domaine.dx;
  double distY = domaine.y0 + domaine.dy;
  double posX = distX / ( getW () * 1. );
  double posY = distY / ( getH () * 1. );
  double x = 0.;
  double y = 0.;
  double norme = 0.;

  int itr = 0;
  // et que pas assez itr
  for ( itr = 0; ( itr < n && norme > 4 ); itr++ ) {
    // tant que ||Z|| < 2
    // calculer x et y ...
    // calculer norme
    x = ( x * x + y * y ) + i;
    y = ( 2 * x * y ) + j;
    norme = x * x + y * y;
  }
  if ( itr == n ) {
    setFloatRGBA ( i, j, 0, 0, 0, 1. );
  } else {
    setHue ( i, j, 1. / itr );
  }
}
