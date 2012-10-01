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
	 * Fonction appelé a chaque fois que glut n'a rien à faire dans la mainLoop.
	 * CàD s'il n'y a pas d'évenents utilisateur (souris,clavier,joystick,repaint,etc...)
	 */
	virtual void idleFunc();

	void fillPBO();

    };

#endif
