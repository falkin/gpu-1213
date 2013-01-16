#ifndef MANDELBROT_H_
#define MANDELBROT_H_

#include "ImageCudaFonctionelMOOs_A.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Mandelbrot : public ImageCudaFonctionelMOOs_A {
public:
  Mandelbrot( const unsigned int w, const unsigned int h, const DomaineMaths& domaine, const int n );
  virtual ~Mandelbrot() {
  }
protected:
  void fillImageGL(uchar4* ptrDevImageGL, int w, int h, const DomaineMaths& domaineNew);
private:
  int _n;
};

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
