#ifndef WIREDRECT2DS_H
#define WIREDRECT2DS_H

#include "Rect2Ds.h"

class CBI_GLIMAGE WiredRect2Ds: public Rect2Ds
    {
    public:
	WiredRect2Ds(int x,int y,int width,int height) : Rect2Ds(x,y,width,height){}
	virtual ~WiredRect2Ds(){};
	void accept(PrimitiveVisitors_I &visitor)
	    {
	    visitor.visite(this);
	    }
    };

#endif
