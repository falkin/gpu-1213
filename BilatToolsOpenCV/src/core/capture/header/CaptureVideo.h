#ifndef CAPTURE_VIDEO_H_
#define CAPTURE_VIDEO_H_

#include "Capture_A.h"

using namespace cv;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * http://opencv.willowgarage.com/wiki/VideoCodecs
 *
 * AVI 'I420' RAW I420 Uncompressed YUV, 4:2:0 chroma subsampled
 *
 * Soft convertion :
 * 	(S1) mencoder
 * 		http://www.mplayerhq.hu/design7/dload.html
 * 			console:  mencoder in.avi -ovc raw -vf format=i420 -oac mp3lame -o out.avi
 * 		http://smplayer.sourceforge.net/
 * 	(S2) VirtualDub
 */
class CaptureVideo: public Capture_A {
  /*--------------------------------------*\
	|*		Constructor		*|
   \*-------------------------------------*/

public:

  CaptureVideo ( const string& videoName, const string& title );
  virtual ~CaptureVideo ( void );

  /*--------------------------------------*\
	|*		Methodes		*|
   \*-------------------------------------*/

public:
  Mat capturer ( void );
  Mat capturerUChar3 ( void );

  /**
   * Temps a attendre entre 2 captures pour respecter fps original
   */
  int getDelayMS (); // Override

  bool isFpsKnown ();
  string getVideoName ();
  int getFps ();
  void printInfo ( void ); // Override

private:

  void configure ();
  VideoCapture* createStream ( const string& videoName );

  /*--------------------------------------*\
	|*		Attributs		*|
   \*-------------------------------------*/

private:

  // Inputs
  string videoName;

  // Outputs
  int delayMS;
  bool isFpsConnu;
  int fps;

};

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
