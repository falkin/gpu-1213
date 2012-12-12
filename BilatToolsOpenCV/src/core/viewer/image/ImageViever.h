#ifndef IMAGE_VIEVER_H_
#define IMAGE_VIEVER_H_

#include <string>
#include "cv.h"
#include "highgui.h"
#include "Chronos.h"

using namespace cv;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class ImageViever
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	ImageViever(const string& titleFrame);
	virtual ~ImageViever(void);

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/**
	 * Warning : call cvWaitKey(1) after,sinon frame bloquer
	 */
	void show(Mat* ptrMatCapture);
	int fps(void);

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:
	//Inputs
	string titleFrame;

	// Tools
	int compteur;
	Chronos chrono;

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
