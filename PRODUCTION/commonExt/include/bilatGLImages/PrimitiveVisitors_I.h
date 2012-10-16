#ifndef PRIMITIVE_VISITOR_H
#define PRIMITIVE_VISITOR_H

#include "envGLImage.h"
//#include "Graphic2Ds.h"
//#include "Line2Ds.h"
//#include "Rect2Ds.h"
//#include "Text2Ds.h"
//#include "WiredRect2Ds.h"

class Graphic2Ds;
class Line2Ds;
class Rect2Ds;
class WiredRect2Ds;
class Text2Ds;

class CBI_GLIMAGE PrimitiveVisitors_I
    {
    public:
	virtual ~PrimitiveVisitors_I()
	    {
	    }

	virtual void visite(Graphic2Ds* graphic2D)=0;
	virtual void visite(Line2Ds* ptrLine2D)=0;
	virtual void visite(Rect2Ds* ptrRect2D)=0;
	virtual void visite(WiredRect2Ds* ptrWiredRect2Ds)=0;
	virtual void visite(Text2Ds* ptrTexte2D)=0;

    };

#endif
