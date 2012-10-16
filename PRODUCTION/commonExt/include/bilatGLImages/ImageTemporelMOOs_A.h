#ifndef IMAGE_TEMPOREL_MOOS_A_H
#define IMAGE_TEMPOREL_MOOS_A_H

#include "ImageMOOs.h"

class CBI_GLIMAGE ImageTemporelMOOs_A: public ImageMOOs
    {
    public:
	ImageTemporelMOOs_A(unsigned int m, unsigned int n,float t=0,float dt=1);
	ImageTemporelMOOs_A(unsigned int m, unsigned int n, unsigned char* ptrTabPixel,float t=0,float dt=1);
	ImageTemporelMOOs_A(const ImageTemporelMOOs_A &imageSource);
	virtual ~ImageTemporelMOOs_A();

	virtual void pixelColor(unsigned int i,unsigned int j,float t)=0;

	float getT() const;
	float getDt() const;

	void setT(float t);

    private:
	void animationStep();

    private:
	float t;
	float dt;
    };

#endif
