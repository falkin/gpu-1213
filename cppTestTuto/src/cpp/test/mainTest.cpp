#include <stdlib.h>
#include <fstream>
#include <string>

#include "cppTest+.h"

#include "TestScalarJunit.h"
#include "TestIntegerJunit.h"

using std::cout;
using std::endl;
using std::string;
using std::ofstream;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

// Already in cppTest+.h
//extern bool runTestConsole(string titre, Test::Suite& test);
//extern bool runTestHtml(string titre, Test::Suite& test);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static bool testInteger(void);
static bool testALL(void);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainTest(void)
    {
    // bool isOk = testInteger();
    bool isOk = testALL();

    cout << "\nisOK = " << isOk << endl;

    return isOk ? EXIT_SUCCESS : EXIT_FAILURE;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

bool testALL()
    {
    Test::Suite testSuite;

    testSuite.add(std::auto_ptr<Test::Suite>(new TestScalarJunit()));
    testSuite.add(std::auto_ptr<Test::Suite>(new TestIntegerJunit()));

    return runTestHtml("TestALL_HTML", testSuite);
    //return runTestConsole("TestALL_Console", testSuite);
    }

bool testInteger(void)
    {
    TestIntegerJunit* ptrTest = new TestIntegerJunit();

    //return runTestHtml("TestIntegerJunit", *ptrTest);
    return runTestConsole("TestIntegerJunit", *ptrTest);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

