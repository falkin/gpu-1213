// Attention : Extension .cu
#include <iostream>
#include "cudaTools.h"
#include "Device.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int addScalarGPU(int a, int b);
bool isAddScalarGPU_Ok(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__global__ static void addScalar(int a, int b, int* ptrC);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isAddScalarGPU_Ok(void)
    {
    cout << endl << "[Hello Cuda 2]" << endl;

    int a = 2;
    int b = 7;

    int sumGPU = addScalarGPU(a, b);
    int sumTheorique = a + b;

    cout << a << "+" << b << "=" << sumGPU << endl;

    return sumGPU == sumTheorique;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

int addScalarGPU(int a, int b)
    {
    int c; // on host (CPU)
    int* ptrDev_c; // on device (GPU)

    dim3 blockPerGrid = dim3(1,1,1); // ou dim3(1,1,1) ou dim3(1) // mais pas  dim3(1, 1,0)
    dim3 threadPerBlock = dim3(1, 1, 1); // ou dim3(1,1) ou dim3(1)

    print(blockPerGrid, threadPerBlock);
    Device::assertDim(blockPerGrid, threadPerBlock);

    HANDLE_ERROR(cudaMalloc((void**) &ptrDev_c, sizeof(int))); // Device memory allocation (*)

    // 1 block de 1 Thread sur le GPU
    addScalar<<<blockPerGrid,threadPerBlock>>>(a,b,ptrDev_c);
    // addScalar<<<1,1>>>(a,b,ptrDev_c); // syntaxe simplifié

    HANDLE_ERROR(cudaMemcpy(&c, ptrDev_c, sizeof(int), cudaMemcpyDeviceToHost));// Device -> Host
    HANDLE_ERROR(cudaFree(ptrDev_c)); // device dispose memory in (*)

    return c;
    }


__global__ void addScalar(int a, int b, int* ptrC)
    {
    *ptrC = a + b;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

