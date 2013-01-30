#include <stdint.h>
#include "cuda_runtime.h"
#include "cudaTools.h"
#include "Chronos.h"

double launchKernelMemoryTransfert ( const void* memory, const size_t size ) {
  Chronos chrono;
  void* ptrDevMemory;
  chrono.start ();
  HANDLE_ERROR( cudaMalloc( &ptrDevMemory, size ) );
  HANDLE_ERROR( cudaMemcpy ( ptrDevMemory, memory, size, cudaMemcpyHostToDevice ) );
  HANDLE_ERROR( cudaDeviceSynchronize () );
  HANDLE_ERROR( cudaFree ( ptrDevMemory ) );

  return chrono.timeFlight ();
}
