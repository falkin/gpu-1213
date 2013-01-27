#include "Mandelbrot.h"
#include "fractal.h"

extern void launchKernelFillImageFractal ( uchar4* ptrDevImageGL, const uint32_t w, const uint32_t h, const DomaineMaths& domaine,
    const FractalType type, const uint32_t n, const float real_c, const float img_c );

Mandelbrot::Mandelbrot ( const uint32_t w, const uint32_t h, const DomaineMaths& domaine, const uint32_t n )
    : ImageCudaFonctionelMOOs_A ( w, h, domaine ), _n ( n ) {
}

void Mandelbrot::fillImageGL ( uchar4* ptrDevImageGL, int w, int h, const DomaineMaths& domaineNew ) {
  launchKernelFillImageFractal ( ptrDevImageGL, w, h, domaineNew, MANDELBROT, _n, 0, 0 );
}
