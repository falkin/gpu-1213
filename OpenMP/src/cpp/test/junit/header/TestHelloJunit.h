#ifndef TEST_HELLO_OMP_JUNIT_H
#define TEST_HELLO_OMP_JUNIT_H

#include "cpptest.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class TestHelloJunit: public Test::Suite
    {
    public:

TestHelloJunit(void);

    private:

	void testHelloOMP1(void);
	void testHelloOMP2(void);

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

