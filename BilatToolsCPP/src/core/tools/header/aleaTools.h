#ifndef ALEATOOLS_H_
#define ALEATOOLS_H_

#include <cstdlib>
#include <time.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/


/**
 * in [a,b]
 * use first once : srand(time(NULL));
 * Attention : pas thread safe
 */
double uniformeAB(double a,double b);

/**
 * in [0,1]
 * use first once : srand(time(NULL));
 */
double uniforme01(void);

/**
 * in [a,b]
 * use first once : srand(time(NULL));
 */
int uniformeAB(int a,int b);

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
