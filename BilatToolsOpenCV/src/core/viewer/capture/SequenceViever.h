#ifndef SEQUENCE_VIEVER_H_
#define SEQUENCE_VIEVER_H_

#include <string>
#include "Capture_A.h"
#include "Chronos.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class SequenceViever
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	SequenceViever(Capture_A* ptrCaptureur);
	virtual ~SequenceViever(void);

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void run();
	int fps(void);

private:

	int timeToWait(Chronos* ptrChrono);

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	//Inputs
	Capture_A* ptrCaptureur;

	// Tools
	bool isStart;

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
