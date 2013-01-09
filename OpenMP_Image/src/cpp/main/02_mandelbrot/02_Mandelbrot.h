#ifndef MANDELBROT_H_
#define MANDELBROT_H_

#include "ImageFonctionelMOOs_A.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

typedef unsigned int Dim;
typedef unsigned int Point;

class Mandelbrot: public ImageFonctionelMOOs_A {
public:
  Mandelbrot ( const Dim w, const Dim h, const DomaineMaths& domaine, const int n );
  virtual ~Mandelbrot () {
  }
protected:
  void fillImage ( const DomaineMaths& domaine );
private:
  void setPixel ( const Point i, const Point j, const DomaineMaths& domaine );

  int n;
};

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
