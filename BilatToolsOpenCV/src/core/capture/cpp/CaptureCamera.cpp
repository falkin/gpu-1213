#include <iostream>
#include "CaptureCamera.h"

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
 * For Camera
 */
CaptureCamera::CaptureCamera(int idCamera,const string&  title, int wAsk, int hAsk) :
	Capture_A(createStream(idCamera),title)

    {
    this->idCamera=idCamera;
    this->wAsk=wAsk;
    this->hAsk=hAsk;

    configure();
    }

CaptureCamera::~CaptureCamera(void)
    {
    VideoCapture* ptrCaptureStream = getVideoCapture();
    delete ptrCaptureStream;
    }

/*------------------*\
 |*	Methode	     *|
 \*-----------------*/

void CaptureCamera::printInfo(void)
    {
    Capture_A::printInfo();

    cout << "\t(w,h) asked = (" << wAsk << "," << hAsk << ") " << endl;

    cout<<endl;
    }

/*------------------*\
 |*	get	     *|
 \*-----------------*/

int CaptureCamera ::getIdCamera()
    {
    return idCamera;
    }


int CaptureCamera::getDelayMS()
    {
    return 0; // On doit attendre sur le port usb, mieux?
    }


/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

VideoCapture* CaptureCamera::createStream(int idCamera)
    {
    VideoCapture* ptrCaptureStream = new VideoCapture(idCamera);

    return ptrCaptureStream;
    }

void CaptureCamera::configure()
    {
    VideoCapture* ptrCaptureStream=getVideoCapture();

    // cout << "(w,h) asked = (" << wAsk << "," << hAsk << ") asked" << endl;

    if (wAsk != -1)
	{
	ptrCaptureStream->set(CV_CAP_PROP_FRAME_WIDTH, wAsk);
	}

    if (hAsk != -1)
	{
	ptrCaptureStream->set(CV_CAP_PROP_FRAME_HEIGHT, hAsk);
	}

    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

