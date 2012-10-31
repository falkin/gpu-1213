#ifndef IMAGE_COMPARATOR_A_H
#define IMAGE_COMPARATOR_A_H
#include "envGLImage.h"
#include "ImageComparaisonResults.h"
#include "ImageMOOs_A.h"

class CBI_GLIMAGE ImageComparator_A
    {
    public:
	ImageComparator_A(ImageMOOs_A* ptrImageSource, ImageMOOs_A* ptrImageTheorique);
	virtual ~ImageComparator_A();

	/**
	 * pixelA and pixelB are composed by 4 unsigned char
	 */
	virtual unsigned int compare(unsigned char* pixelA, unsigned char* pixelB)=0;

	virtual ImageComparaisonResults run(unsigned int epsilon);

	ImageMOOs_A* getImageSource();
	ImageMOOs_A* getImageTheorique();

    protected:
	ImageMOOs_A* ptrImageSource;
	ImageMOOs_A* ptrImageTheorique;
    };

#endif
