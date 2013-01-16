#include "HeaterMOO.h"
#include "tab2DTools.h"
#include "Calibreurs.h"
#include <iostream>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

#define SPACE_HEATER 10
#define GRID_HEATER 50
using std::cout;
using std::endl;

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
HeaterMOO::HeaterMOO ( const unsigned int width, const unsigned int height, const float k, const unsigned int blindItr )
    : ImageMOOs ( width, height ), _k ( k ), _blindItr ( blindItr ), _imgHeater ( 0 ), _imgInit ( 0 ), _imgA ( 0 ), _imgB (
        0 ) {
  initImages ();
}

HeaterMOO::~HeaterMOO () {
  int w = getW ();
  free ( _imgHeater, w );
  free ( _imgInit, w );
  free ( _imgA, w );
  free ( _imgB, w );
}

void HeaterMOO::addHeater( const unsigned int x, const unsigned int y, const HEATER_TYPE type ) {
  double temperature = 0.0;
  switch ( type ) {
  case HEATER:
    temperature = 1.0;
    break;
  case COOLER:
    temperature = 0.2;
    break;
  default:
    break;
  }
  _imgHeater[y][x] = temperature;
}

void HeaterMOO::animationStep ( bool& isNeedUpdateView ) {
  for ( int i = 0; i < _blindItr; i++ ) {
    diffuse ( _imgA, _imgB );
    erase ( _imgHeater, _imgB );
    double** tmp = _imgA; // swapping
    _imgA = _imgB;
    _imgB = tmp;
  }

  fillImage ( _imgA );
  isNeedUpdateView = true;
  // A devient B, B devient A
  // tester a chaque fois isNeedUpdateView pour faire en sorte qu'il update une fois sur blindItr!
}
/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/
void HeaterMOO::initImages () {
  int h = getH ();
  int w = getW ();
  alloc ( _imgHeater, w, h );
  alloc ( _imgInit, w, h );
  alloc ( _imgA, w, h );
  alloc ( _imgB, w, h );
  init ( _imgHeater, w, h, .0 );
  init ( _imgInit, w, h, .0 );
  init ( _imgA, w, h, .0 );
  init ( _imgB, w, h, .0 );
  //_imgHeater[w / 2][h / 2] = 1.0;   // TODO: Faire une initialisation du heater propre!
  for ( int i = (w / 2) - GRID_HEATER; i < (w / 2) + GRID_HEATER; i += SPACE_HEATER ) {
    for ( int j = (w / 2) - GRID_HEATER; j < (w / 2) + GRID_HEATER; j += SPACE_HEATER ) {
      _imgHeater[i][j] = 1.0;
    }
  }
  erase ( _imgHeater, _imgInit );
  diffuse ( _imgInit, _imgA );
  erase ( _imgHeater, _imgA );
  fillImage ( _imgA );

}

void HeaterMOO::fillImage ( double** img ) {
  int h = getH ();
  int w = getW ();
  Calibreurs calibreur ( 0, 1, 0.7, 0 );
  for ( int i = 1; i <= w; i++ ) {
    for ( int j = 1; j <= h; j++ ) {
      double temperature = img[i - 1][j - 1];
      float hue = calibreur.calibrate ( temperature );
      setHue ( i, j, hue );
    }
  }
}

void HeaterMOO::erase ( double** src, double** dest ) {
  int h = getH ();
  int w = getW ();
  for ( int i = 0; i < w; i++ ) {
    for ( int j = 0; j < h; j++ ) {
      if ( src[i][j] != .0 ) {
        dest[i][j] = src[i][j];
      }
    }
  }
}

void HeaterMOO::diffuse ( double** src, double** dest ) {
  // modèle 1: check les bounds
  int h = getH ();
  int w = getW ();
  for ( int i = 0; i < w; i++ ) {
    for ( int j = 0; j < h; j++ ) {
      double old = src[i][j];
      double neighbours = sumNeighbours ( src, i, j );
      dest[i][j] = old + _k * ( neighbours - ( 4 * old ) );
    }
  }
}

double HeaterMOO::sumNeighbours ( double** img, const unsigned int i, const unsigned int j ) const {
  double sum = .0;
  if ( inBounds ( i, j - 1 ) ) sum += img[i][j - 1];
  if ( inBounds ( i, j + 1 ) ) sum += img[i][j + 1];
  if ( inBounds ( i - 1, j ) ) sum += img[i - 1][j];
  if ( inBounds ( i + 1, j ) ) sum += img[i + 1][j];
  return sum;
}
/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

