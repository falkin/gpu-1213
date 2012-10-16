#include <stdlib.h>
#include <iostream>

#include "cppTest+.h"
#include "TestHelloJunit.h"


using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Procedure Importated				*|
 \*---------------------------------------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Procedure Private 				*|
 \*---------------------------------------------------------------------*/

static bool testALL(void);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainTest(void)
    {
    bool isOk = testALL();

    cout<<"\n-------------------------------------------------"<<endl;
    cout<<"End Main : isOk = "<<isOk<<endl;

    return isOk ? EXIT_SUCCESS : EXIT_FAILURE;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

bool testALL(void)
    {
    Test::Suite testSuite;

    testSuite.add(std::auto_ptr<Test::Suite>(new TestHelloJunit()));



    return runTestHtml("TestALL_HTML", testSuite);
   //return runTestConsole("TestALL_Console", testSuite);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

