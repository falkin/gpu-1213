#ifndef GLIMAGECOMPARATORS_H
#define GLIMAGECOMPARATORS_H
#include "envGLImage.h"
#include "ImageComparator_A.h"
#include "Courbe2DViewers.h"
#include "ImageMOOs.h"
#include "Courbe2DComparatorMOOs.h"
#include "GLImages.h"

class CBI_GLIMAGE GLImageComparators
    {
    public:
	GLImageComparators(ImageComparator_A* ptrImageComparator);
	virtual ~GLImageComparators();

	void run();
    private :
	void createImageDeltaHSB();
	void createCourbe2DComparator();
    private :
	ImageComparator_A* ptrImageComparator;
	ImageComparaisonResults comparaisonResult;
	Courbe2DComparatorMOOs* ptrCourbe2DMOO;
	ImageMOOs* ptrImageDeltaHsb;

	GLImages* ptrGLImageDeltaHsb;
	Courbe2DViewers* ptrCourbe2DViewer;

    };

#endif
