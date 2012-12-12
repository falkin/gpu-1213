#ifndef CAPTURE_A_H_
#define CAPTURE_A_H_

#include <string>

#include "cv.h"
#include "highgui.h"
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
class Capture_A
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	Capture_A(VideoCapture* ptrCaptureStream,const string&  title);
	virtual ~Capture_A(void);

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	VideoCapture* getVideoCapture();
	int getW(void);
	int getH(void);
	string getTitle();
	Chronos getChronos();
	int fps();

	bool isOpened(void);
	int nbOctetImage();
	long nbCapture();

	virtual void printInfo(void);

	/**
	 * Temps a attendre entre 2 captures pour respecter fps original
	 */
	int dtMS();

	/**
	 * To be call periodicly to obtain image
	 */
	Mat capturer(void);

	// Tools
	static uchar4* castToUChar4(uchar* ptrTab);
	static uchar4* castToUChar4(Mat* ptrMap);

    protected:

    private:

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	string title;
	VideoCapture* ptrCaptureStream;

	// Tools
	Mat matCaptureSrc;

	// Outputs
	float w;
	int h;
	Mat matCaptureDest;
	long compteurCapture;
	Chronos chrono;

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
