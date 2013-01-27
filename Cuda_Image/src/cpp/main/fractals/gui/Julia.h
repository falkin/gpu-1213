#ifndef JULIA_H_
#define JULIA_H_

#include "ImageCudaFonctionelMOOs_A.h"

class Julia: public ImageCudaFonctionelMOOs_A {
public:
  Julia ( const uint32_t w, const uint32_t h, const DomaineMaths& domaine, const uint32_t n, const float real_c, const float img_c );
  virtual ~Julia () {
  }
protected:
  void fillImageGL ( uchar4* ptrDevImageGL, int w, int h, const DomaineMaths& domaineNew );
private:
  uint32_t _n;
  float _real_c;
  float _img_c;
};

#endif 
