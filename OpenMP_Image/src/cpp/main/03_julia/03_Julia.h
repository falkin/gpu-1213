#ifndef JULIA_H_
#define JULIA_H_

#include "ImageFonctionelMOOs_A.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

typedef unsigned int Dim;
typedef unsigned int Point;

class Julia: public ImageFonctionelMOOs_A {
public:
  Julia ( const Dim w, const Dim h, const DomaineMaths& domaine, const int n, const float real_c, const float img_c, const bool omp = false  );
  virtual ~Julia () {}
protected:
  void fillImage ( const DomaineMaths& domaine );
private:
  void setPixel ( const Point i, const Point j, const DomaineMaths& domaine );

  int n;
  float real_c;
  float img_c;
  bool _omp;
};

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
