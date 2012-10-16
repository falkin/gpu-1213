#ifndef IMAGEMOOS_A_H
#define IMAGEMOOS_A_H

#include "envGLImage.h"

#define NB_CHAR_PIXEL 4
#define OFFSET_RED 0
#define OFFSET_GREEN 1
#define OFFSET_BLUE 2
#define OFFSET_ALPHA 3

#include "Graphic2Ds.h"

class CBI_GLIMAGE ImageMOOs_A
    {
    public:
	ImageMOOs_A(unsigned int width,unsigned int height);
	ImageMOOs_A(const ImageMOOs_A &imageSource);
	virtual ~ImageMOOs_A();

	virtual void animationStep(bool& isNeedUpdateView)=0;
	virtual void paintPrimitives(Graphic2Ds& ptrGraphic2D);
	virtual unsigned char* getPtrTabPixels()=0;


	inline unsigned int getM() const
	    {
	    return width;
	    }

	inline unsigned int getN() const
	    {
	    return height;
	    }

	inline unsigned int getDx() const
	    {
	    return width;
	    }

	unsigned int getDy() const
	    {
	    return height;
	    }

	unsigned int getW() const
	    {
	    return width;
	    }

	unsigned int getH() const
	    {
	    return height;
	    }

	unsigned int getSizeOctet() const;

    protected:
	unsigned int width;
	unsigned int height;

    };

#endif
