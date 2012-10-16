#include "TestHelloJunit.h"
#include "vectorTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern void helloOMP1(void);
extern void helloOMP2(void);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

TestHelloJunit::TestHelloJunit(void)
    {
    TEST_ADD(TestHelloJunit::testHelloOMP1);
    TEST_ADD(TestHelloJunit::testHelloOMP2);
    }

void TestHelloJunit::testHelloOMP1(void)
    {
    helloOMP1();
    }

void TestHelloJunit::testHelloOMP2(void)
    {
    helloOMP2();
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

