#ifndef PRIMITIVES_A_H
#define PRIMITIVES_A_H

#include "envGLImage.h"
#include "PrimitiveVisitors_I.h"

class CBI_GLIMAGE Primitives_A
    {
    public:
	Primitives_A()
	    {
	    isNeedToDelete = false;
	    }
	;
	Primitives_A(const Primitives_A &source)
	    {
	    }
	;
	virtual ~Primitives_A()
	    {
	    }
	;
	virtual void accept(PrimitiveVisitors_I &visitor)=0;

    public:
	bool isNeedToDelete;
    };

#endif
