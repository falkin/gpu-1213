#include "Julia.h"
#include "fractal.h"

extern void launchKernelFillImageFractal ( uchar4* ptrDevImageGL, const uint32_t w, const uint32_t h, const DomaineMaths& domaine,
    const FractalType type, const uint32_t n, const float real_c, const float img_c );

Julia::Julia ( const uint32_t w, const uint32_t h, const DomaineMaths& domaine, const uint32_t n, const float real_c, const float img_c )
    : ImageCudaFonctionelMOOs_A ( w, h, domaine ), _n ( n ), _real_c ( real_c ), _img_c ( img_c ) {
}

void Julia::fillImageGL ( uchar4* ptrDevImageGL, int w, int h, const DomaineMaths& domaineNew ) {
  launchKernelFillImageFractal ( ptrDevImageGL, w, h, domaineNew, JULIA, _n, _real_c, _img_c );
}
