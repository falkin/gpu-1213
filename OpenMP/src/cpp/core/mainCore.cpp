#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include "Chronos.h"
using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*         Declaration                     *|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*     Imported        *|
 \*-------------------------------------*/

extern void helloOMP1(void);
extern void helloOMP2(void);

extern double ComputePI1 ( unsigned long long intervals, int threads = 0 );
extern double ComputePI2 ( unsigned long long intervals, int threads = 0 );
extern double ComputePI3 ( unsigned long long intervals, int threads = 0 );
extern double ComputePI4 ( unsigned long long intervals, int threads = 0 );
extern double ComputePI5 ( unsigned long long intervals, int threads = 0 );
extern double ComputePI6 ( unsigned long long intervals, int threads = 0 );
extern double ComputePI7 ( unsigned long long intervals, int threads = 0 );
extern double ComputePI8 ( unsigned long long intervals, int threads = 0 );

/*--------------------------------------*\
 |*     Public          *|
 \*-------------------------------------*/

int mainCore(void);

/*--------------------------------------*\
 |*     Private         *|
 \*-------------------------------------*/

static bool useHello(void);
static bool usePI ( void );


/*----------------------------------------------------------------------*\
 |*         Implementation                  *|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*     Public          *|
 \*-------------------------------------*/

int mainCore(void) {
    bool isOk = true;
    Chronos chrono;
    chrono.start();

    //isOk &= useHello();

    isOk &= usePI();

    cout << "\n-------------------------------------------------" << endl;
    cout << "End Main : isOk = " << isOk << endl;

    return isOk ? EXIT_SUCCESS : EXIT_FAILURE;
}

/*--------------------------------------*\
 |*     Private         *|
 \*-------------------------------------*/

bool useHello(void) {
    helloOMP1();
    helloOMP2();

    return true;
}

bool usePI ( void ) {
    ComputePI1 ( 1000000000 );
    ComputePI2 ( 1000000000 );
    ComputePI3 ( 1000000000 );
    ComputePI4 ( 1000000000 );
    ComputePI5 ( 1000000000 );
    ComputePI6 ( 1000000000 );
    ComputePI7 ( 1000000000 );
    ComputePI8 ( 1000000000 );
    return true;
}
/*----------------------------------------------------------------------*\
 |*         End                     *|
 \*---------------------------------------------------------------------*/

