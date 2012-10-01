#include <iostream>
#include <limits.h>


using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Importation 					*|
 \*---------------------------------------------------------------------*/

extern int mainCore(void);
extern int mainTest(void);

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
    return  isTest?mainTest():mainCore();
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

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

