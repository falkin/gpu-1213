#ifndef IMAGE_CUDA_SERVICE_MOOS_H
#define IMAGE_CUDA_SERVICE_MOOS_H

#include "ImageCudaMOOs_A.h"

class ImageCudaServiceMOOs : public ImageCudaMOOs_A
    {
    public:
	ImageCudaServiceMOOs(unsigned int w, unsigned int h);
	virtual ~ImageCudaServiceMOOs();

	void performKernel(uchar4* ptrDevPixels, int w, int h);
	void animationStep(bool &isNeedUpdateView);

	void setPtrDevImageSource(uchar4* ptrDevImageSource);
	void setNeedUpdate(bool isNeedUpdate);
    private:
	bool isNeedUpdate;
	uchar4* ptrDevImageSource;
    };

#endif
