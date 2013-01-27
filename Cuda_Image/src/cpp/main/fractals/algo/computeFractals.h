#ifndef COMPUTE_H_
#define COMPUTE_H_

#include <stdint.h>
#include "DomaineMaths.h"
#include "ColorToolCuda.h"

/**
 *
 */
struct DomainMathsCuda {
  double _x0;
  double _y0;
  double _dx;
  double _dy;
};

/**
 *
 */
DomainMathsCuda createDomaineMathsCuda ( const DomaineMaths& domain, const uint32_t w, const uint32_t h ) {
  DomainMathsCuda cudaDomain = { domain.x0, domain.y0, ( domain.x1 - domain.x0 ) / w, ( domain.y1 - domain.y0 ) / h };
  return cudaDomain;
}

/**
 *
 */
__device__
void toXY ( const DomainMathsCuda& domain, const uint32_t i, const uint32_t j, double& x, double& y ) {
  x = domain._x0 + ( j * domain._dx );
  y = domain._y0 + ( i * domain._dy );
}

/**
 *
 */
__device__
void displayMandelbrotXY ( const double x0, const double y0, const uint32_t n, uchar4* ptrDevImageGL, const uint32_t s ) {
  double x = 0;
  double y = 0;
  double xtemp = 0;
  uint32_t itr = 0;

  while ( itr < n && ( x * x + y * y ) < 4 ) {
    xtemp = ( x * x - y * y ) + x0;
    y = ( 2 * x * y ) + y0;
    x = xtemp;
    itr++;
  }
  bool diverge = ( itr == n && ( x * x + y * y ) < 4 );
  if ( diverge ) {
    ptrDevImageGL[s].x = ptrDevImageGL[s].y = ptrDevImageGL[s].z = 0;
  } else {
    ColorToolCuda::HSB_TO_RVB ( (float) ( itr - 1 ) / n, 1, 1, ptrDevImageGL[s].x, ptrDevImageGL[s].y, ptrDevImageGL[s].z );
  }
  ptrDevImageGL[s].w = 255;
}

/**
 *
 */
__device__
void displayJuliaXY ( const double x0, const double y0, const uint32_t n, const float real_c, const float img_c, uchar4* ptrDevImageGL,
    const uint32_t s ) {
  double x = x0;
  double y = y0;
  double xtemp = 0;
  uint32_t itr = 0;

  while ( itr < n && ( x * x + y * y ) < 4 ) {
    xtemp = ( x * x - y * y ) + real_c;
    y = ( 2 * x * y ) + img_c;
    x = xtemp;
    itr++;
  }
  bool diverge = ( itr == n && ( x * x + y * y ) < 4 );
  if ( diverge ) {
    ptrDevImageGL[s].x = ptrDevImageGL[s].y = ptrDevImageGL[s].z = 0;
  } else {
    ColorToolCuda::HSB_TO_RVB ( (float) ( itr - 1 ) / n, 1, 1, ptrDevImageGL[s].x, ptrDevImageGL[s].y, ptrDevImageGL[s].z );
  }
  ptrDevImageGL[s].w = 255;
}

#endif
