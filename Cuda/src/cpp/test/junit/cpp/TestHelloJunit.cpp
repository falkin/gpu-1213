#include "TestHelloJunit.h"
#include "Device.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern void helloCuda(void);
extern bool isAddScalarGPU_Ok(void);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructor		*|
 \*-------------------------------------*/

TestHelloJunit::TestHelloJunit(int deviceId)
    {
    this->deviceId=deviceId;

    TEST_ADD(TestHelloJunit::testDeviceInfo);
    TEST_ADD(TestHelloJunit::testHelloCuda);
    TEST_ADD(TestHelloJunit::testAdd);
    }

/*--------------------------------------*\
 |*		Methodes		*|
 \*-------------------------------------*/

void TestHelloJunit::testHelloCuda(void)
    {
    helloCuda();
    }

void TestHelloJunit::testAdd(void)
    {
    TEST_ASSERT(isAddScalarGPU_Ok() == true);
    }

void TestHelloJunit::testDeviceInfo(void)
    {
    Device::print(deviceId,"Test on device : ");
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

