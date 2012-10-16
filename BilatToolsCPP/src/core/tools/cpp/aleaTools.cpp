#include <math.h>
#include <cstdlib>
#include "aleaTools.h"

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


/**
 * in [a,b]
 * use first once : srand(time(NULL));
 * Attention : pas thread safe
 */
double uniformeAB(double a,double b)
    {
    return a+uniforme01()*(b-a);
    }

/**
 * in [0,1]
 * use first once : srand(time(NULL));
 * Attention : pas thread safe
 */
double uniforme01(void)
    {
    // rand in [0,RAND_MAX]
    return rand()/(double)RAND_MAX;
    }

/**
 * in [a,b]
 * use first once : srand(time(NULL));
 * Attention : pas thread safe
 */
int uniformeAB(int a,int b)
    {
    // rand in [0,RAND_MAX]
    return a+rand()%(b-a+1);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
