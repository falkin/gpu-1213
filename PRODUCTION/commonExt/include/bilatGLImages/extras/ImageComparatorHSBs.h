
#ifndef IMAGE_COMPARATOR_HSBS_H
#define IMAGE_COMPARATOR_HSBS_H

#include "ImageComparator_A.h"

class CBI_GLIMAGE ImageComparatorHSBs: public ImageComparator_A
    {
    public:
	ImageComparatorHSBs(ImageMOOs_A* ptrImageSource, ImageMOOs_A* ptrImageTheorique);
	virtual ~ImageComparatorHSBs();
	/**
	 * pixelA and pixelB are composed by 4 unsigned char
	 */
	float compare(unsigned char* pixelA, unsigned char* pixelB);
    };

#endif
