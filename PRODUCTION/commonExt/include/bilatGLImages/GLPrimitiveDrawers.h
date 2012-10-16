#ifndef GL_PRIMITIVE_DRAWERS_H
#define GL_PRIMITIVE_DRAWERS_H

#include "envGLImage.h"
#include "PrimitiveVisitors_I.h"
#include "GLUTTextRenderers.h"
#include "Line2Ds.h"
#include "Rect2Ds.h"
#include "Text2Ds.h"
#include "WiredRect2Ds.h"
#include "Graphic2Ds.h"

class CBI_GLIMAGE GLPrimitiveDrawers: public PrimitiveVisitors_I
    {
    public:
	GLPrimitiveDrawers();
	virtual ~GLPrimitiveDrawers();

	void visite(Graphic2Ds* graphic2D);
	void visite(Line2Ds* ptrLine2D);
	void visite(Rect2Ds* ptrRect2D);
	void visite(Text2Ds* ptrTexte2D);
	void visite(WiredRect2Ds* ptrWiredRect2D);

    private:
	GLUTTextRenderers glutTextRenderer;
    };

#endif
