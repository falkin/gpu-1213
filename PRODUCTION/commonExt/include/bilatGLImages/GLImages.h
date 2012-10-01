#ifndef GLIMAGES_H
#define GLIMAGES_H

#include "envGLImage.h"
#include "GLImageAPIWindows.h"

#include "ImageMOOs.h"

class CBI_GLIMAGE GLImages: public GLImageAPIWindows
    {
    public:

	/**
	 * (pxFrame,pyFrame) is the position of the upper left corner of the frame in screen space.
	 */
	GLImages(ImageMOOs* ptrImageMOO, bool isAnimationEnable = true, int pxFrame = 0, int pyFrame = 0);

	virtual ~GLImages();



	ImageMOOs* getPtrImageMOO();

    protected:

	/**
	 * Fonction appel� a chaque fois que glut n'a rien � faire dans la mainLoop.
	 * C�D s'il n'y a pas d'�venents utilisateur (souris,clavier,joystick,repaint,etc...)
	 */
	virtual void idleFunc();

	void fillPBO();

    };

#endif
