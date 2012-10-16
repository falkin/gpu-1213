#ifndef CUDA_TOOLS_H_
#define CUDA_TOOLS_H_

#include <string>

#include "builtin_types.h"
#include "cuda_runtime.h"
#include "curand.h"
#include "cublas_api.h"
//#include "cuda.h"

using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

#define HANDLE_ERROR( error ) (cudaHandleError( error, __FILE__, __LINE__ ))

void cudaHandleError(cudaError_t error, const char *file, int line); //cuda
void cudaHandleError(curandStatus_t statut, const char *file, int line); // curand
void cudaHandleError(cublasStatus_t cublasStatus,const char *file, int line); // cublas

void print(const dim3& dim, string titrePre,string titrePost);
void print(const dim3& blockPerGrid,const  dim3& threadPerBlock);


void check_CUDA_Error(const char *message=NULL);

/**
 * Example 1
 * 	nbThreadTotal=256
 * 	nbBlock=128
 * 	threadPerBlock=2
 * Example 2
 * 	nbThreadTotal=257
 * 	nbBlock=128
 * 	threadPerBlock=3
 */
int threadPerBlock(int nTotal, int nbBlock);

int dim(const dim3& dim);



#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

