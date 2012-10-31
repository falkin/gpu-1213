
#ifndef GLUT_TEXT_RENDERERS_H
#define GLUT_TEXT_RENDERERS_H

#include "envGLTools.h"
#include "Fonts.h"

#include <string>
using std::string;

class CBI_GLTOOLS  GLUTTextRenderers
    {
    public:
	GLUTTextRenderers();
	virtual ~GLUTTextRenderers();


	static void renderBitmapChars(float x, float y, float z, const char *string, void* font);

	static void renderBitmapString(float x,float y,float z,string texte,const Fonts& font);

	/**
	 * all value are relative to viewport, ie not in pixels !
	 */
	static void renderBitmapStringCentered(float x, float y,int frameWidth,int frameHight, string title,const Fonts& font);

    };

#endif
