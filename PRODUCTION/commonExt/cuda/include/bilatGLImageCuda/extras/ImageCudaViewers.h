#ifndef IMAGE_CUDA_VIEWERS_H
#define IMAGE_CUDA_VIEWERS_H

#include "ImageCudaViewerMultiples.h"

class CBI_GLIMAGE_CUDA ImageCudaViewers: public ImageCudaViewerMultiples
    {
    public:
	ImageCudaViewers(ImageCudaMOOs_A* ptrImageCudaMOO, bool useAnimation = true, bool useSelection = false, int pxFrame = 0, int pyFrame = 0);
	ImageCudaViewers(ImageCudaFonctionelMOOs_A* ptrImageCudaFonctionel, bool useAnimation = true, bool useSelection = true, int pxFrame = 0,
		int pyFrame = 0);
	virtual ~ImageCudaViewers();

	void run();
	static void init(int argc, char** argv);
    };

#endif
