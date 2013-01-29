#ifndef CAPTURE_A_H_
#define CAPTURE_A_H_

#include <string>

#include <opencv2/opencv.hpp>
#include "cudaTools.h"
#include "Chronos.h"

using namespace cv;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * http://opencv.willowgarage.com/wiki/VideoCodecs
 */
class Capture_A {
  /*--------------------------------------*\
	|*		Constructor		*|
   \*-------------------------------------*/

public:

  Capture_A ( VideoCapture* ptrCaptureStream, const string& title );
  virtual ~Capture_A ( void );

  /*--------------------------------------*\
	|*		Methodes		*|
   \*-------------------------------------*/

public:

  VideoCapture* getVideoCapture ();
  int getW ( void );
  int getH ( void );
  string getTitle ();
  Chronos getChronos ();
  int fps ();

  bool isOpened ( void );
  int nbOctetImage ();
  long nbCapture ();

  virtual void printInfo ( void );

  /**
   * Temps a attendre entre 2 captures pour respecter fps original
   */
  int dtMS ();

  /**
   * To be call periodicly to obtain image
   */
  virtual Mat capturer ( void );
  virtual Mat capturerUChar3 ( void );

  // Tools
  static uchar4* castToUChar4 ( uchar* ptrTab );
  static uchar4* castToUChar4 ( Mat* ptrMat );
  static inline uchar3* castToUChar3 ( uchar* ptrTab ) {
    return (uchar3*) ptrTab;
  }
  static inline uchar3* castToUChar3 ( Mat* ptrMat ) {
    return (uchar3*) ptrMat->data;
  }

protected:

private:

  /*--------------------------------------*\
	|*		Attributs		*|
   \*-------------------------------------*/

protected:

  Mat matCaptureDest;
  Mat matCaptureSrc;
  long compteurCapture;
  Chronos chrono;
  VideoCapture* ptrCaptureStream;

private:

  // Inputs
  string title;

  // Outputs
  float w;
  int h;

};

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
