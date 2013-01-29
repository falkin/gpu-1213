#ifndef HEATERMOO_H_
#define HEATERMOO_H_

#include "ImageMOOs.h"

enum HEATER_TYPE {
  HEATER, COOLER
};

class HeaterMOO: public ImageMOOs {
public:
  HeaterMOO ( const uint32_t width, const uint32_t height, const float k, const uint32_t blindItr, const bool omp = false );
  virtual ~HeaterMOO ();
  void animationStep ( bool& isNeedUpdateView );
  void addHeater ( const uint32_t x, const uint32_t y, const HEATER_TYPE type );
private:
  void initImages ();
  void fillImage ( double** img );
  void erase ( double** src, double** dest );
  void diffuse ( double** src, double** dest );
  double sumNeighbours ( double** img, const uint32_t i, const uint32_t j ) const;
  inline bool inBounds ( const uint32_t i, const uint32_t j ) const {
    return ( i >= 0 ) && ( j >= 0 ) && ( i < width ) && ( j < height );
  }
  float _k;
  uint32_t _blindItr;
  bool _omp;
  double** _imgHeater;
  double** _imgInit;
  double** _imgA;
  double** _imgB;
};

#endif
