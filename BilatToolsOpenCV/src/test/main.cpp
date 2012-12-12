#include <iostream>

#include "CaptureVideo.h"
#include "CaptureCamera.h"
#include "Capture_A.h"
#include "SequenceViever.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static bool useVideo(void);
static bool useCamera(void);
static void show(Capture_A* ptrCaptureur);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int main(void)
    {
    bool isUseVideo = true;

    if (isUseVideo)
	{
	return useVideo();
	}
    else
	{
	return useCamera();
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

bool useVideo(void)
    {
    string videoName = "C:\\Users\\bilat\\Desktop\\nasaFHD.avi";
    string title = "Tuto Video";

    CaptureVideo captureur(videoName, title);

    if (captureur.isOpened())
	{
	show(&captureur);
	}

    return true;
    }

bool useCamera(void)
    {
    int idCamera = 0;
    string title = "Tuto Camera";

    // CaptureCamera captureur(idCamera, title,320,160);
    CaptureCamera captureur(idCamera, title);

    if (captureur.isOpened())
	{
	show(&captureur);
	}

    return true;
    }

void show(Capture_A* ptrCaptureur)
    {
    SequenceViever sequenceViever(ptrCaptureur);
    sequenceViever.run();
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

