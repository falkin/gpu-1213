#ifndef HEATERMOO_H_
#define HEATERMOO_H_

#include "ImageMOOs.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

enum HEATER_TYPE {
  HEATER,
  COOLER
};

class HeaterMOO: public ImageMOOs {
public:
  HeaterMOO ( const unsigned int width, const unsigned int height, const float k, const unsigned int blindItr );
  virtual ~HeaterMOO ();
  void animationStep ( bool& isNeedUpdateView );
  void addHeater( const unsigned int x, const unsigned int y, const HEATER_TYPE type );
private:
  void initImages ();
  void fillImage ( double** img );
  void setPixel ( int i, int j, float t );
  void erase ( double** src, double** dest );
  void diffuse ( double** src, double** dest );
  double sumNeighbours( double** img, const unsigned int i, const unsigned int j ) const;
  inline bool inBounds ( const unsigned int i, const unsigned int j ) const {
    return ( i >= 0 ) && ( j >= 0 ) && ( i < width ) && ( j < height );
  }
  float _k;
  unsigned int _blindItr;
  double** _imgHeater;
  double** _imgInit;
  double** _imgA;
  double** _imgB;
};

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
