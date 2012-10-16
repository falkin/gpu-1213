#ifndef IMAGEVIEWERSINGLES_H
#define IMAGEVIEWERSINGLES_H

#include "ImageViewerMultiples.h"

class CBI_GLIMAGE ImageViewers: public ImageViewerMultiples
    {
    public:
	ImageViewers(ImageMOOs* ptrImageMOO, bool useAnimation = false, bool useSelection = false, int pxFrame = 0, int pyFrame = 0);
	ImageViewers(ImageFonctionelMOOs_A* ptrImageFonctionel, bool useAnimation = false, bool useSelection = true, int pxFrame = 0, int pyFrame = 0);
	virtual ~ImageViewers();

	/**
	 * Attention appel bloquant !
	 */
	void run();
	static void init(int argc,char** argv);
    };

#endif
