#ifndef GLCOURBE2D_H
#define GLCOURBE2D_H

#include "envGLTools.h"
#include "VertexBufferObject.h"
#include "Courbe2DMOOs.h"

class CBI_GLTOOLS GLCourbe2Ds
    {
    public:
	GLCourbe2Ds(Courbe2DMOOs* ptrCourbe2D);

	virtual ~GLCourbe2Ds();

	Courbe2DMOOs *getPtrCourbe2D() const;

	virtual void update();
	virtual void init(void);
	virtual void display(void);
	virtual void release();

    private:
	void createVertexVBO();
    private:
	//Input
	Courbe2DMOOs* ptrCourbe2D;

	//GL
	VertexBufferObject* vboVertex;
    };

#endif
