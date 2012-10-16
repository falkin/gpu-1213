#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "cudaTools.h"
#include "Device.h"
#include "stringTools.h"

using std::string;
using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int threadPerBlock(int nbThreadTotal, int nbBlock)
    {
    //return ceil(nbThreadTotal / (double) nbBlock);

    // mieux

    return (nbThreadTotal + (nbBlock - 1)) / nbBlock;
    }

void print(const dim3& dim, string titrePre, string titrePost)
    {
    cout << titrePre << "(" << dim.x << "," << dim.y << "," << dim.z << ") " << titrePost << endl;
    }

void print(const dim3& blockPerGrid, const dim3& threadPerBlock)
    {
    int mpCount = Device::getMPCount();
    int warpSize = Device::getWarpSize();

    int blockCount = dim(blockPerGrid);
    int threadCountMP = dim(threadPerBlock);

    string messageBlock = "";
    string messageThread = "";

    if (blockCount < mpCount || blockCount % mpCount != 0)
	{
	messageBlock = "blockCount = " + toString(blockCount) + " : Warning : For best performance, blockCount should be a multiple of #MP="
		+ toString(mpCount);
	}

    if (threadCountMP < warpSize || threadCountMP % warpSize != 0)
	{
	messageThread = "threadCountMP = " + toString(threadCountMP) + " : Warning : For best performance, threadCountMP  be a multiple of |warp|="
		+ toString(warpSize);
	}

    print(blockPerGrid, "BlockPerGrid   ", messageBlock);
    print(threadPerBlock, "ThreadPerBlock ", messageThread);
    }

/**
 * Cuda
 */
void cudaHandleError(cudaError_t error, const char *file, int line)
    {
    if (error != cudaSuccess)
	{
	cout << "[CUDA ERROR] : " << cudaGetErrorString(error) << " in " << file << " at ligne " << line << endl;
	exit (EXIT_FAILURE);
	}
    }

/**
 * Curand
 */
void cudaHandleError(curandStatus_t statut, const char *file, int line)
    {
    if (statut != CURAND_STATUS_SUCCESS)
	{
	cout << "[CURAND ERROR] : " << statut << " in " << file << " at ligne " << line << endl;
	exit (EXIT_FAILURE);
	}
    }

/**
 * Cublas
 */
void cudaHandleError(cublasStatus_t cublasStatus, const char *file, int line)
    {

    if (cublasStatus != CUBLAS_STATUS_SUCCESS)
	{
	switch (cublasStatus)
	    {
	    case CUBLAS_STATUS_INVALID_VALUE:
		cout << "[CUBLAS ERROR] :  CUBLAS_STATUS_INVALID_VALUE " << " in " << file << " at line " << line << endl;
		break;
	    case CUBLAS_STATUS_NOT_INITIALIZED:
		cout << "[CUBLAS ERROR] : CUBLAS_STATUS_NOT_INITIALIZED " << " in " << file << " at line " << line << endl;
		break;
	    case CUBLAS_STATUS_INTERNAL_ERROR:
		cout << "[CUBLAS ERROR] : CUBLAS_STATUS_INTERNAL_ERROR " << " in " << file << " at line " << line << endl;
		break;
	    case CUBLAS_STATUS_MAPPING_ERROR:
		cout << "[CUBLAS ERROR] : CUBLAS_STATUS_MAPPING_ERROR " << " in " << file << " at line " << line << endl;
		break;

	    case CUBLAS_STATUS_ALLOC_FAILED:
		cout << "[CUBLAS ERROR] : CUBLAS_STATUS_ALLOC_FAILED " << " in " << file << " at line " << line << endl;
		break;
	    case CUBLAS_STATUS_ARCH_MISMATCH:
		cout << "[CUBLAS ERROR] :  CUBLAS_STATUS_ARCH_MISMATCH" << " in " << file << " at line " << line << endl;
		break;
	    case CUBLAS_STATUS_EXECUTION_FAILED:
		cout << "[CUBLAS ERROR] : CUBLAS_STATUS_EXECUTION_FAILED" << " in " << file << " at line " << line << endl;
		break;
	    default:
		cout << "[CUBLAS ERROR] : Unknown error !" << " in " << file << " at line " << line << endl;
		break;
	    }
	exit (EXIT_FAILURE);
	}
    }

void check_CUDA_Error(const char *message)
    {
    cudaError_t error = cudaGetLastError();
    if (error != cudaSuccess)
	{
	if (message != NULL)
	    {
	    fprintf(stderr, "[CUDA ERROR] : Kernel Execution Failed : %s: %s\n\n", message, cudaGetErrorString(error));
	    }
	else
	    {
	    fprintf(stderr, "[CUDA ERROR] : Kernel Execution Failed : %s\n\n", cudaGetErrorString(error));
	    }
	exit(-1);
	}
    }

int dim(const dim3& dim)
    {
    return dim.x * dim.y * dim.z;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

