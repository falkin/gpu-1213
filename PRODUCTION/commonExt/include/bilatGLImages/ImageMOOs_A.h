#ifndef IMAGEMOOS_A_H
#define IMAGEMOOS_A_H

#include "envGLImage.h"
#include "Graphic2Ds.h"
#include <iostream>
#include <string>
using std::string;
using std::ostream;

#define NB_CHAR_PIXEL 4
#define OFFSET_RED 0
#define OFFSET_GREEN 1
#define OFFSET_BLUE 2
#define OFFSET_ALPHA 3

class CBI_GLIMAGE ImageMOOs_A
    {
    public:
	ImageMOOs_A(unsigned int width,unsigned int height);
	ImageMOOs_A(const ImageMOOs_A &imageSource);
	virtual ~ImageMOOs_A();

	virtual void animationStepAPI(bool& isNeedUpdateView);
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

	virtual void print(ostream& stream) const;

	/**
	 * call image.print(stream)
	 */
	CBI_GLIMAGE friend ostream& operator<<(ostream& stream, const ImageMOOs_A& image);


    protected:
	unsigned int width;
	unsigned int height;

    };



#endif
