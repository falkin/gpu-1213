#include "Mandelbrot.h"

extern void launchKernelFillImage ( uchar4* ptrDevImageGL, const int w, const int h, const DomaineMaths& domaine, int n );
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
Mandelbrot::Mandelbrot ( const unsigned int w, const unsigned int h, const DomaineMaths& domaine, const int n )
    : ImageCudaFonctionelMOOs_A ( w, h, domaine ), _n ( n ) {
}
/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/
void Mandelbrot::fillImageGL ( uchar4* ptrDevImageGL, int w, int h, const DomaineMaths& domaineNew ) {
  launchKernelFillImage ( ptrDevImageGL, w, h, domaineNew, _n );
}
/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

