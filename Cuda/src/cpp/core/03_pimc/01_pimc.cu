// Attention : Extension .cu

#include <iostream>
#include "cudaTools.h"
#include "Device.h"
#include "Indice1D.h"
#include <stdio.h>
#include <curand_kernel.h>
#include <cmath>

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void pimcCuda(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__global__ static void kernelReduction(curandState* tabGeneratorThread, int* ptrDevTab, int n);
__global__ static void kernelGenRandom(curandState* tabGeneratorThread, int deviceId);
__device__ static void step(int* tab, int half);
__device__ void copyGMtoSM(int* tabSM, int* tabGM, int n);
__device__ void copySMtoGM(int* tabGM, int* tabSM, int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

#define THREAD_PER_BLOCK_X 32
#define THREAD_PER_BLOCK_Y 1
#define THREAD_PER_BLOCK_Z 1

#define BLOCK_PER_GRID_X 16
#define BLOCK_PER_GRID_Y 1
#define BLOCK_PER_GRID_Z 1

#define NB_BLOCK  (BLOCK_PER_GRID_X*BLOCK_PER_GRID_Y*BLOCK_PER_GRID_Z)
#define NB_THREAD_PER_BLOCK (THREAD_PER_BLOCK_X*THREAD_PER_BLOCK_Y*THREAD_PER_BLOCK_Z)
#define NB_THREAD (NB_BLOCK*NB_THREAD_PER_BLOCK)

/**
 * http://developer.download.nvidia.com/compute/cuda/4_2/rel/toolkit/docs/online/index.html
 * resumer commande cuda
 */
void pimcCuda(void)
    {
    dim3 blockPerGrid = dim3(BLOCK_PER_GRID_X, BLOCK_PER_GRID_Y, BLOCK_PER_GRID_Z); // ou dim3(1, 1) // mais pas  dim3(1, 1,0)
    dim3 threadPerBlock = dim3(THREAD_PER_BLOCK_X, THREAD_PER_BLOCK_Y, THREAD_PER_BLOCK_Z); // ou dim3(1,1)

    print(blockPerGrid, threadPerBlock);
    Device::assertDim(blockPerGrid, threadPerBlock);

    int nbDevice = 6;//Device::getDeviceCount();
    //Device::loadCudaDriverDeviceAll();
    for (int i = 0; i < nbDevice; i++)
	Device::loadCudaDriver(i);

#pragma omp parallel for //reduction(+:count) private(x,y,z)
    for (int i = 0; i < nbDevice; i++)
	{
	HANDLE_ERROR(cudaSetDevice(i));
	int deviceId = 0;
	HANDLE_ERROR(cudaGetDevice(&deviceId));
	printf("%d\n",deviceId);

	double nglobal = pow(2, 30);
	int nperThread = nglobal / NB_THREAD;
	//printf("%d\n", nperThread);

	int* ptrHostTab = new int[NB_BLOCK];
	for (int i = 0; i < NB_BLOCK; i++)
	    ptrHostTab[i] = 0;

	int* ptrDevTab = NULL;
	curandState* ptrDevtabGeneratorThread = NULL;

	size_t tabsize = NB_BLOCK * sizeof(int);

	HANDLE_ERROR(cudaMalloc((void**) &ptrDevtabGeneratorThread, NB_THREAD * sizeof(curandState)));

	HANDLE_ERROR(cudaMalloc((void**) &ptrDevTab, tabsize));

	kernelGenRandom<<<blockPerGrid,threadPerBlock>>>(ptrDevtabGeneratorThread,deviceId);
	check_CUDA_Error("kernelGenRandom");

	kernelReduction<<<blockPerGrid,threadPerBlock>>>(ptrDevtabGeneratorThread,ptrDevTab,nperThread);
	check_CUDA_Error("kernelReduction");

	HANDLE_ERROR(cudaMemcpy(ptrHostTab,ptrDevTab,tabsize,cudaMemcpyDeviceToHost));

	HANDLE_ERROR(cudaDeviceSynchronize());

	long sum = 0;
	for (int i = 0; i < NB_BLOCK; i++)
	    {
	    sum += ptrHostTab[i];
	    }

	double pi = (double) sum / nglobal * 4;
	cout.precision(15);
	cout << pi << endl;

	HANDLE_ERROR(cudaFree(ptrDevtabGeneratorThread));
	HANDLE_ERROR(cudaFree(ptrDevTab));
	delete[] ptrHostTab;
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/
__global__ void kernelGenRandom(curandState* tabGeneratorThread, int deviceId)
    {
    int tid = Indice1D::tid();

    int deltaSeed = deviceId * 1000000;
    int deltaSequence = deviceId * 100;
    int deltaOffset = deviceId * 100;

    int seed = 1234 + deltaSeed;
    int sequenceNumber = tid + deltaSequence;
    int offset = deltaOffset;

    curand_init(seed, sequenceNumber, offset, &tabGeneratorThread[tid]);

    }

__global__ void kernelReduction(curandState* tabGeneratorThread, int* ptrDevTab, int n)
    {
    int tid = Indice1D::tid();
    int tidLocal = threadIdx.x + blockDim.x * threadIdx.y;

    int count = 0;
    curandState localState = tabGeneratorThread[tid];

    __shared__ int tabSM[NB_THREAD_PER_BLOCK];
    tabSM[tidLocal] = 0;

    float x, y;
    for (int i = 0; i < n; i++)
	{
	x = curand_uniform(&localState);
	y = curand_uniform(&localState);
	if (x * x + y * y <= 1)
	    count++;
	}
    tabSM[tidLocal] = count;

    __syncthreads();

    int half = NB_THREAD_PER_BLOCK / 2;
    while (half > 0)
	{
	step(tabSM, half);
	half /= 2;
	}
    copySMtoGM(ptrDevTab, tabSM, n);

    }

__device__ void step(int* tab, int half)
    {
    int tidLocal = threadIdx.x + blockDim.x * threadIdx.y;
    int tabindex = tidLocal;
    if (tidLocal < half)
	{
	tab[tabindex] += tab[tabindex + half];
	}
    __syncthreads();
    }

__device__ void copyGMtoSM(int* tabSM, int* tabGM, int n)
    {
    int tidLocal = threadIdx.x + blockDim.x * threadIdx.y;
    if (tidLocal < n)
	{
	tabSM[tidLocal] = tabGM[tidLocal];
	}
    __syncthreads();
    }

__device__ void copySMtoGM(int* tabGM, int* tabSM, int n)
    {
    int tidLocal = threadIdx.x + blockDim.x * threadIdx.y;
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

