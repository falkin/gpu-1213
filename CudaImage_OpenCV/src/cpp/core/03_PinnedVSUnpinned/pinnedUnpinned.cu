#include <stdint.h>
#include "cuda_runtime.h"
#include "cudaTools.h"
#include "Chronos.h"

double launchKernelMemoryTransfert ( const uint32_t w, const uint32_t h, const void* memory, const size_t memory_size ) {
  Chronos chrono;
  size_t size = w * h * memory_size;
  void* ptrDevMemory;
  chrono.start ();
  HANDLE_ERROR( cudaMalloc( &ptrDevMemory, size ) );
  HANDLE_ERROR( cudaMemcpy ( ptrDevMemory, memory, size, cudaMemcpyHostToDevice ) );
  HANDLE_ERROR( cudaDeviceSynchronize () );
  HANDLE_ERROR( cudaFree ( ptrDevMemory ) );

  return chrono.timeFlight ();
}
