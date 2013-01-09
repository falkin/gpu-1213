#include "SequenceViever.h"
#include "ImageViever.h"
#include <iostream>

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

SequenceViever::SequenceViever ( Capture_A* ptrCaptureur )

{
  this->ptrCaptureur = ptrCaptureur;
  this->isStart = false;
}

SequenceViever::~SequenceViever ( void ) {
  // rien
}

void SequenceViever::run () {
  if ( !isStart ) {
    isStart = true;

    ptrCaptureur->printInfo ();

    string titleFrame = ptrCaptureur->getTitle () + "[q to quit]";
    ImageViever imageViever ( titleFrame );

    Chronos chrono;
    char key = 'a'; //disons
    while ( key != 'q' ) {
      Mat image = ptrCaptureur->capturer ();

      imageViever.show ( &image );

      int timetoWaitYet = timeToWait ( &chrono );
      key = cvWaitKey ( max ( 1, timetoWaitYet ) ); // attention 1 min, pour respecter cadence original

      if ( ptrCaptureur->nbCapture () % 60 == 0 ) //disons
          {
        cout << "fps = " << ptrCaptureur->fps () << endl;
      }
    }

    isStart = false;
  }
}

int SequenceViever::fps () {
  return ptrCaptureur->fps ();
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

int SequenceViever::timeToWait ( Chronos* ptrChrono ) {
  int timeElapseMS = ptrChrono->timeFlight () * 1000;
  int timeToWaitTheorique = ptrCaptureur->dtMS ();

  int timetoWaitYet = timeToWaitTheorique - timeElapseMS;
  timetoWaitYet = max ( 0, timetoWaitYet ); // 0 si negatif

//    cout<<"timeToWaitTheorique "<<timeToWaitTheorique<<endl;
//    cout<<"timeElapseMS "<<timeElapseMS<<endl;
//    cout<<"timetoWaitYet "<<timetoWaitYet<<endl;

  ptrChrono->stop ();
  ptrChrono->start ();

  return timetoWaitYet;
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

