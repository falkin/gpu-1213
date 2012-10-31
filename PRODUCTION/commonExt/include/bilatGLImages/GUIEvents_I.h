#ifndef GUI_EVENTS_H
#define GUI_EVENTS_H

#include "envGLImage.h"
#include "DomaineEcrans.h"
class CBI_GLIMAGE GUIEvents_I
    {
    public:
	GUIEvents_I(){};
	virtual ~GUIEvents_I(){};

	virtual void initPerformed()=0;
	virtual void displayPerformed()=0;
	virtual void reshapePerformed(int w, int h)=0;
	virtual void mouseMovedPerformed(int x, int y)=0;
	virtual void mousePressedPerformed(int button, int state, int x, int y)=0;
	virtual void keyPressedPerformed(unsigned char key, int x, int y)=0;
	virtual void specialKeyPressedPerformed(int key, int x, int y)=0;

	/**
	 * then selection is performed with the mouse, 3 arguments :
	 *	1) selected domaine in frame coordinate
	 *	2) dx is the screen width in pixLa clel
	 *	3) dy is the screen height in pixel
	 **/
	virtual void selectionPerformed(DomaineEcrans& domaine, int dx, int dy)=0;
    };

#endif
