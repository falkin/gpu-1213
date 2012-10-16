#ifndef IMAGE_CUDA_MOOS_A_H
#define IMAGE_CUDA_MOOS_A_H

#include "builtin_types.h"
#include "envGLImageCudas.h"
#include "ImageMOOs_A.h"
class CBI_GLIMAGE_CUDA ImageCudaMOOs_A : public ImageMOOs_A
    {
    public:
	ImageCudaMOOs_A(unsigned int w, unsigned int h);
	virtual ~ImageCudaMOOs_A();



	virtual void fillImageGL(uchar4* ptrDevImageGL, int w, int h)=0; //ptrDevImageGL zone memoire commune OpenGL et Cuda

	virtual void animationStep(bool &isNeedUpdateView);

	/**
	 * Recuperation des pixels de l'image
	 * call fillImageGL
	 */
	unsigned char* getPtrTabPixels();
    };

#endif
