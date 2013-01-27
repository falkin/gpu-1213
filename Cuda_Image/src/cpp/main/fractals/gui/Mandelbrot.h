#ifndef MANDELBROT_H_
#define MANDELBROT_H_

#include "ImageCudaFonctionelMOOs_A.h"

class Mandelbrot : public ImageCudaFonctionelMOOs_A {
public:
  Mandelbrot( const uint32_t w, const uint32_t h, const DomaineMaths& domaine, const uint32_t n );
  virtual ~Mandelbrot() {
  }
protected:
  void fillImageGL(uchar4* ptrDevImageGL, int w, int h, const DomaineMaths& domaineNew);
private:
  uint32_t _n;
};

#endif
