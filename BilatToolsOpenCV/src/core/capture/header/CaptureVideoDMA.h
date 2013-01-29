#ifndef CAPUTREVIDEODMA_H_
#define CAPUTREVIDEODMA_H_

#include "Capture_A.h"

class CaptureVideoDMA: public Capture_A {
public:
  CaptureVideoDMA ( const string& videoName, const string& title );
  virtual ~CaptureVideoDMA ();
  Mat capturer ( void );
  Mat capturerUChar3 ( void );

  int getDelayMS ();

  bool isFpsKnown ();
  string getVideoName ();
  int getFps ();
  void printInfo ( void );

private:

  void configure ();
  VideoCapture* createStream ( const string& videoName );

  // Inputs
  string videoName;

  // Outputs
  int delayMS;
  bool isFpsConnu;
  int fps;

  // Optimize
  uchar3* _data;
};

#endif 
