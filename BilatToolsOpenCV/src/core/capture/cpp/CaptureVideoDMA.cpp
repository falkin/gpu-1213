#include <iostream>
#include "CaptureVideoDMA.h"
#include "cuda_runtime.h"

using std::cerr;
using std::cout;
using std::endl;

/**
 *
 */
CaptureVideoDMA::CaptureVideoDMA ( const string& videoName, const string& title )
    : Capture_A ( createStream ( videoName ), title ) {
  this->videoName = videoName;
  configure ();
}

/**
 *
 */
CaptureVideoDMA::~CaptureVideoDMA ( void ) {
  VideoCapture* ptrCaptureStream = getVideoCapture ();
  delete ptrCaptureStream;
}

/**
 *
 */
Mat CaptureVideoDMA::capturer ( void ) {
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

  // TODO: do not transform from uchar3 to uchar4, alpha value not needed!
  cvtColor ( matCaptureSrc, matCaptureDest, CV_8U, 4 ); //CV_8U CV_RGB2GRAY // 0 keep same chanel // 4 permet par exemple d'ajouter la couche alpha \ufffd\ufffd\ufffd rvb (pour une video ou webcam)

  return matCaptureDest; //castToUChar4(matCapture.data);
}

/**
 *
 */
Mat CaptureVideoDMA::capturerUChar3 ( void ) {
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

  // TODO: do not transform from uchar3 to uchar4, alpha value not needed!
  //cvtColor ( matCaptureSrc, matCaptureDest, CV_8U, 4 ); //CV_8U CV_RGB2GRAY // 0 keep same chanel // 4 permet par exemple d'ajouter la couche alpha \ufffd\ufffd\ufffd rvb (pour une video ou webcam)

  return matCaptureSrc; //castToUChar4(matCapture.data);
}

/**
 *
 */
void CaptureVideoDMA::printInfo ( void ) {
  Capture_A::printInfo ();

  cout << "\tvideo name = " << videoName << endl;

  if ( isFpsConnu ) {
    cout << "\tfps source = " << fps << endl;
  } else {
    cout << "\tfps source = Inconnu" << endl;
  }

  cout << endl;
}

/**
 *
 */
int CaptureVideoDMA::getDelayMS () {
  return delayMS;
}

/**
 *
 */
int CaptureVideoDMA::getFps () {
  return fps;
}

/**
 *
 */
bool CaptureVideoDMA::isFpsKnown () {
  return isFpsConnu;
}

/**
 *
 */
string CaptureVideoDMA::getVideoName () {
  return videoName;
}

/**
 *
 */
VideoCapture* CaptureVideoDMA::createStream ( const string& videoName ) {
  VideoCapture* ptrVideoCapture = new VideoCapture ( videoName );

  return ptrVideoCapture;
}

/**
 *
 */
void CaptureVideoDMA::configure () {
  VideoCapture* ptrCaptureStream = getVideoCapture ();

  // cudaHostAlloc -> 1980 * 1080 * sizeof(uchar3)
  size_t data_size = getH () * getW () * sizeof(uchar3);
  HANDLE_ERROR( cudaHostAlloc ( (void**) &_data, data_size, cudaHostAllocDefault ) );
  // cf: Mat::Mat(int _rows, int _cols, int _type, void* _data, size_t _step)
  matCaptureSrc = Mat ( getH (), getW (), CV_8UC3, _data );

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
