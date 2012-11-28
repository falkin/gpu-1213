#include <iostream>
#include <stdlib.h>
#include "limits.h"
#include "Device.h"
#include "cudaTools.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern void helloCuda(void);
extern void reductionCuda(void);
extern void pimcCuda(void);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainCore(int deviceId);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static bool useHello(void);
static bool useReduction(void);
static bool usePIMonteCarlo(void);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainCore(int deviceId)
    {
    //Device::print(deviceId, "Execute on device : ");

    bool isOk = true;
    //isOk &= useHello();
    //isOk &= useReduction();
    isOk &= usePIMonteCarlo();

    cout << "\nisOK = " << isOk << endl;
    cout << "\nEnd : mainCore" << endl;

    return isOk ? EXIT_SUCCESS : EXIT_FAILURE;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

bool useHello(void)
    {
    helloCuda();
    return true;
    }

bool useReduction(void)
    {
    reductionCuda();
    return true;
    }

bool usePIMonteCarlo(void)
    {
    pimcCuda();
    return true;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

