#ifndef TEST_HELLO_JUNIT_H
#define TEST_HELLO_JUNIT_H

#include "cpptest.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class TestHelloJunit: public Test::Suite
    {
    public:

	TestHelloJunit(int deviceId);

    private:

	void testHelloCuda(void);
	void testAdd(void);
	void testDeviceInfo(void);

    private:

	int deviceId;

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

