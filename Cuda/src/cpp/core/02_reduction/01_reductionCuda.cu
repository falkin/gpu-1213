// Attention : Extension .cu

#include <iostream>
#include "cudaTools.h"
#include "Device.h"
#include "Indice2D.h"
#include <stdio.h>

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void reductionCuda(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__global__ static void kernelReduction(float* ptrDevTab, int n);
__device__ static void step(float* tab, int half);
__device__ void copyGMtoSM(float* tabSM, float* tabGM, int n);
__device__ void copySMtoGM(float* tabGM, float* tabSM, int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * http://developer.download.nvidia.com/compute/cuda/4_2/rel/toolkit/docs/online/index.html
 * resumer commande cuda
 */
void reductionCuda(void)
    {
    dim3 blockPerGrid = dim3(16, 1, 1); // ou dim3(1, 1) // mais pas  dim3(1, 1,0)
    dim3 threadPerBlock = dim3(32, 1, 1); // ou dim3(1,1)

    print(blockPerGrid, threadPerBlock);
    Device::assertDim(blockPerGrid, threadPerBlock);

    int n = 8;

    float* ptrHostTab = new float[n];
    float* ptrDevTab = NULL;
    for (int i = 0; i < n; i++)
	ptrHostTab[i] = 2;

    printf("input data host side: ");
    for (int i = 0; i < n; i++)
	printf("%f,", ptrHostTab[i]);
    printf("\n");

    size_t tabsize = n * sizeof(float);

    HANDLE_ERROR(cudaMalloc((void**) &ptrDevTab, tabsize));
    HANDLE_ERROR(cudaMemcpy(ptrDevTab,ptrHostTab,tabsize,cudaMemcpyHostToDevice));

    kernelReduction<<<blockPerGrid,threadPerBlock>>>(ptrDevTab,n);

    check_CUDA_Error("kernelReduction");

    HANDLE_ERROR(cudaMemcpy(ptrHostTab,ptrDevTab,tabsize,cudaMemcpyDeviceToHost));

    HANDLE_ERROR(cudaDeviceSynchronize());

    printf("output data host side: ");
    for (int i = 0; i < n; i++)
	printf("%f,", ptrHostTab[i]);
    printf("\n");

    HANDLE_ERROR(cudaFree(ptrDevTab));
    delete[] ptrHostTab;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__global__ void kernelReduction(float* ptrDevTab, int n)
    {
    int tid = Indice2D::tid();
    int tidLocal = Indice2D::tidLocalBlock();

    __shared__ float tabSM[10];
    tabSM[tidLocal] = 0;

    copyGMtoSM(tabSM, ptrDevTab, n);
    int half = n / 2;
    while (half > 0)
	{
	step(tabSM, half);
	half /= 2;
	}
    copySMtoGM(ptrDevTab, tabSM, n);
    }

__device__ void step(float* tab, int half)
    {
    int tidLocal = Indice2D::tidLocalBlock();
    int tabindex = tidLocal;
    if (tidLocal < half)
	{
	tab[tabindex] += tab[tabindex + half];
	}
    __syncthreads();
    }

__device__ void copyGMtoSM(float* tabSM, float* tabGM, int n)
    {
    int tidLocal = Indice2D::tidLocalBlock();
    if (tidLocal < n)
	{
	tabSM[tidLocal] = tabGM[tidLocal];
	}
    __syncthreads();
    }

__device__ void copySMtoGM(float* tabGM, float* tabSM, int n)
    {
    int tidLocal = Indice2D::tidLocalBlock();
    int bid = (blockIdx.y * gridDim.x) + blockIdx.x;
    if (tidLocal == 0)
	{
	tabGM[bid] = tabSM[0];
	}
    __syncthreads();
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

