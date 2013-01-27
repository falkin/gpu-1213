#include "HeaterImageCuda.h"
#include <stdint.h>

extern void initKernelHeatDispersion ( const uint32_t w, const uint32_t h, const float k, const uint32_t blindItr );
extern void launchKernelHeatDispersion ( const uint32_t w, const uint32_t h, const float k, const uint32_t blindItr,
    uchar4* ptrDevImageGL );

HeaterImageCuda::HeaterImageCuda ( const uint32_t w, const uint32_t h, const float k, const uint32_t blindItr )
    : ImageCudaMOOs_A ( w, h ), _k ( k ), _blindItr ( blindItr ) {
  initKernelHeatDispersion ( w, h, _k, _blindItr );
}

HeaterImageCuda::~HeaterImageCuda () {
}

void HeaterImageCuda::animationStep ( bool& isNeedUpdateView ) {
  isNeedUpdateView = true;
}

void HeaterImageCuda::fillImageGL ( uchar4* ptrDevImageGL, int w, int h ) {
  launchKernelHeatDispersion ( w, h, _k, _blindItr, ptrDevImageGL );
}
