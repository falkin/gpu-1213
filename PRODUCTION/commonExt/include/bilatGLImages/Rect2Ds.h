#ifndef RECT_2DS_H
#define RECT_2DS_H

#include "Primitives_A.h"

class CBI_GLIMAGE Rect2Ds: public Primitives_A
    {
    public:
	/*
	 * (x,y) coin superieur gauche
	 */
	Rect2Ds(int x, int y, int width, int height);
	virtual ~Rect2Ds();

	void accept(PrimitiveVisitors_I &visitor);

	void setXY(int x,int y);
	void setSize(int width,int height);

	inline int getX()
	    {
	    return x;
	    }

	inline int getY()
	    {
	    return y;
	    }

	inline int getWidth()
	    {
	    return width;
	    }

	inline int getHeight()
	    {
	    return height;
	    }



    public:
	int x;
	int y;
	int width;
	int height;
    };

#endif
