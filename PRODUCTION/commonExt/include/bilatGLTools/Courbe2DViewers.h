#ifndef COURBE_2D_VIEWERS_H
#define COURBE_2D_VIEWERS_H

#include "envGLTools.h"
#include "GLUTWindowCustomiser_A.h"
#include "GLCourbe2Ds.h"


class CBI_GLTOOLS Courbe2DViewers: public GLUTWindowCustomiser_A
    {
    public:
	Courbe2DViewers(GLCourbe2Ds* ptrGLCourbe2D, string title, int width, int height, int pxFrame = 0, int pyFrame = 0);
	virtual ~Courbe2DViewers();
    protected:
	virtual void update();
	virtual void init(void);
	virtual void display(void);
	virtual void reshape(int w, int h);
	virtual void release();
	virtual void centrerReduire();
    protected:
	GLCourbe2Ds* ptrGLCourbe2D;
	bool isNeedUpdate;
    };

#endif
