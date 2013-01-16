#ifndef DOMAINE_MATHS_H_
#define DOMAINE_MATHS_H_

#include "DomaineMaths.h"

class DomaineMathsCuda {
public:
  DomaineMathsCuda ( double x0, double y0, double x1, double y1 )
      : _x0 ( x0 ), _y0 ( y0 ), _x1 ( x1 ), _y1 ( y1 ) {
  }

  DomaineMathsCuda ( const DomaineMaths& domaineSource )
      : _x0 ( domaineSource.x0 ), _y0 ( domaineSource.y0 ), _x1 ( domaineSource.x1 ), _y1 ( domaineSource.y1 ) {
  }

  ~DomaineMathsCuda () {
  }

  __device__
  void toXY ( const int i, const int j, double** x, double** y ) const {
    *x = x1 () + ( j * dx () );
    *y = y1 () + ( i * dy () );
  }

  __device__
  double dx () const {
    return _x1 - _x0;
  }

  __device__
  double dy () const {
    return _y1 - _y0;
  }

  __device__
  double x0 () const {
    return _x0;
  }

  __device__
  double y0 () const {
    return _y0;
  }

  __device__
  double x1 () const {
    return _x1;
  }

  __device__
  double y1 () const {
    return _y1;
  }

private:
  double _x0;
  double _y0;
  double _x1;
  double _y1;
};

#endif
