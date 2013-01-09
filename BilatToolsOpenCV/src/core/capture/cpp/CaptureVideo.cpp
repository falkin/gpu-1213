#include <iostream>
#include "CaptureVideo.h"

using std::cerr;
using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*------------------*\
 |*  Constructeur     *|
 \*-----------------*/

/**
 * For VIdeo
 */
CaptureVideo::CaptureVideo ( const string& videoName, const string& title )
    : Capture_A ( createStream ( videoName ), title ) {
  this->videoName = videoName;
  configure ();
}

CaptureVideo::~CaptureVideo ( void ) {
  VideoCapture* ptrCaptureStream = getVideoCapture ();
  delete ptrCaptureStream;
}

/*------------------*\
 |*	Methode	     *|
 \*-----------------*/

Mat CaptureVideo::capturer ( void ) {
  if ( compteurCapture == 0 ) {
    Chronos chrono;
    this->chrono = chrono;
  }

  compteurCapture++;
  if ( !ptrCaptureStream->read ( matCaptureSrc ) ) {
    ptrCaptureStream->set ( CV_CAP_PROP_POS_FRAMES, 0 );
    compteurCapture = 0;
    ptrCaptureStream->read ( matCaptureSrc );
  }

  cvtColor ( matCaptureSrc, matCaptureDest, CV_8U, 4 ); //CV_8U CV_RGB2GRAY // 0 keep same chanel // 4 permet par exemple d'ajouter la couche alpha � rvb (pour une video ou webcam)

  return matCaptureDest; //castToUChar4(matCapture.data);
}

void CaptureVideo::printInfo ( void ) {
  Capture_A::printInfo ();

  cout << "\tvideo name = " << videoName << endl;

  if ( isFpsConnu ) {
    cout << "\tfps source = " << fps << endl;
  } else {
    cout << "\tfps source = Inconnu" << endl;
  }

  cout << endl;
}

/*------------------*\
 |*	get	     *|
 \*-----------------*/

int CaptureVideo::getDelayMS () {
  return delayMS;
}

int CaptureVideo::getFps () {
  return fps;
}

/*------------------*\
 |*	is	     *|
 \*-----------------*/

bool CaptureVideo::isFpsKnown () {
  return isFpsConnu;
}

string CaptureVideo::getVideoName () {
  return videoName;
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

VideoCapture* CaptureVideo::createStream ( const string& videoName ) {
  VideoCapture* ptrVideoCapture = new VideoCapture ( videoName );

  return ptrVideoCapture;
}

void CaptureVideo::configure () {
  VideoCapture* ptrCaptureStream = getVideoCapture ();

  this->fps = ptrCaptureStream->get ( CV_CAP_PROP_FPS );

  // cout << "fps video source (" << videoName << ") = ";

  if ( fps != 0 ) {
    this->isFpsConnu = true;
    this->delayMS = 1000 / fps;

    //cout << fps << endl << endl;
  } else {
    this->isFpsConnu = false;
    this->delayMS = 0;

    //cout << "fps unknown" << endl << endl;
  }
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

