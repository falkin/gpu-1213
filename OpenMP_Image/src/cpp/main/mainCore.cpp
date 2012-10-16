#include <stdlib.h>
#include <iostream>
#include "Chronos.h"
#include "ImageViewers.h"
#include "01_RipplingSimple.h"
using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*         Declaration                     *|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*     Imported        *|
 \*-------------------------------------*/

//extern double ComputePI8 ( unsigned long long intervals, int threads = 0 );
/*--------------------------------------*\
 |*     Public          *|
 \*-------------------------------------*/

int mainCore( void );

/*--------------------------------------*\
 |*     Private         *|
 \*-------------------------------------*/

static bool useRippling( void );

/*----------------------------------------------------------------------*\
 |*         Implementation                  *|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*     Public          *|
 \*-------------------------------------*/

int mainCore( void ) {
	bool isOk = true;
	Chronos chrono;
	chrono.start();

	//isOk &= useHello();

	isOk &= useRippling();

	cout << "\n-------------------------------------------------" << endl;
	cout << "End Main : isOk = " << isOk << endl;

	return isOk ? EXIT_SUCCESS : EXIT_FAILURE;
}

/*--------------------------------------*\
 |*     Private         *|
 \*-------------------------------------*/

bool useRippling ( void ) {
	RipplingSimple r ( 256, 0.1 );
	ImageViewers viewer( &r, true );
	viewer.run();

	return true;
}

/*----------------------------------------------------------------------*\
 |*         End                     *|
 \*---------------------------------------------------------------------*/

