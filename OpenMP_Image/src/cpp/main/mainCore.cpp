#include <stdlib.h>
#include <iostream>
#include "Chronos.h"
#include "ImageViewers.h"
#include "RipplingMOO.h"
#include "02_Mandelbrot.h"
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

int mainCore(void);

/*--------------------------------------*\
 |*     Private         *|
 \*-------------------------------------*/

static bool useRippling(void);
static bool useMandelbrot(void);

/*----------------------------------------------------------------------*\
 |*         Implementation                  *|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*     Public          *|
 \*-------------------------------------*/

int mainCore(void)
    {
    bool isOk = true;
    Chronos chrono;
    chrono.start();

    //isOk &= useHello();

    //isOk &= useRippling ();
    isOk &= useMandelbrot();

    cout << "\n-------------------------------------------------" << endl;
    cout << "End Main : isOk = " << isOk << endl;

    return isOk ? EXIT_SUCCESS : EXIT_FAILURE;
    }

/*--------------------------------------*\
 |*     Private         *|
 \*-------------------------------------*/

bool useRippling(void)
    {
    RipplingMOO ripplingA(600, 600, 0, 0.5);

    bool isAnimationEnable = true;
    ImageViewers imageViewer(&ripplingA, isAnimationEnable);
    ImageViewers::runALL();

    return true;
    }

bool useMandelbrot(void)
    {
    float x0 = -2.1;
    float y0 = 1.3;
    float dx = 2.9;
    float dy = 2.6;
    Mandelbrot mandel(512, 512, DomaineMaths(x0, y0, dx, dy));
    ImageViewers viewer(&mandel);
    ImageViewers::runALL();
    return true;
    }

/*----------------------------------------------------------------------*\
 |*         End                     *|
 \*---------------------------------------------------------------------*/

