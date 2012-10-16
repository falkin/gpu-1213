#include <iostream>
#include <limits.h>
#include "Device.h"


using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Importation 					*|
 \*---------------------------------------------------------------------*/


 int mainTest(void);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int main(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void rappelTypeSize(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

int main(void)
    {
    rappelTypeSize();

    bool isTest=true;
    return mainTest();
    }

void rappelTypeSize(void)
    {
    cout<<endl;
    cout<<"Rappel type size (from limits.h) "<<endl;
    cout<<"SHORT_MAX = "<<SHRT_MAX<<"      : "<<sizeof(short)<<" Octets"<<endl;
    cout<<"INT_MAX   = "<<INT_MAX<<" : "<<sizeof(int)<<" Octets"<<endl;
    cout<<"LONG_MAX  = "<<LONG_MAX<<" : "<<sizeof(long)<<" Octets"<<endl;
    cout<<endl;
    }

int mainTest(void)
    {
    Device::printALL("ALL GPU Found");

    return EXIT_SUCCESS;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

