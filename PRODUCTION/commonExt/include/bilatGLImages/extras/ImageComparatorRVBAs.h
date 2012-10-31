#ifndef IMAGE_COMPARATOR_RVBAS_H
#define IMAGE_COMPARATOR_RVBAS_H

#include "ImageComparator_A.h"

class CBI_GLIMAGE ImageComparatorRVBAs: public ImageComparator_A
    {
    public:
	ImageComparatorRVBAs(ImageMOOs_A* ptrImageSource, ImageMOOs_A* ptrImageTheorique);
	virtual ~ImageComparatorRVBAs();

	/**
	 * pixelA and pixelB are composed by 4 unsigned char
	 */
	virtual unsigned int compare(unsigned char* pixelA, unsigned char* pixelB);

    };

#endif
