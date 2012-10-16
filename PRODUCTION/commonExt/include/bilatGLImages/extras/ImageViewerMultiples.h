#ifndef IMAGEVIEWERS_H
#define IMAGEVIEWERS_H

#include "GUIEvents_I.h"
#include "GLImageFonctionelSelections.h"

class CBI_GLIMAGE ImageViewerMultiples: public GUIEvents_I
    {
    public:
	ImageViewerMultiples(ImageMOOs* ptrImageMOO,bool useAnimation=false,bool useSelection=false, int pxFrame = 0, int pyFrame = 0);
	ImageViewerMultiples(ImageFonctionelMOOs_A* ptrImageFonctionel,bool useAnimation=false,bool useSelection=true, int pxFrame = 0, int pyFrame = 0);
	virtual ~ImageViewerMultiples();
	GLImages* getGLImage();

	void updateView();

    protected:
	virtual void initPerformed();
	virtual void displayPerformed();
	virtual void reshapePerformed(int w, int h);
	virtual void mouseMovedPerformed(int x, int y);
	virtual void mousePressedPerformed(int button, int state, int x, int y);
	virtual void keyPressedPerformed(unsigned char key, int x, int y);
	virtual void specialKeyPressedPerformed(int key, int x, int y);

	/**
	 * then selection is performed with the mouse, 3 arguments :
	 *	1) selected domaine in frame coordinate
	 *	2) dx is the screen width in pixel
	 *	3) dy is the screen height in pixel
	 **/
	virtual void selectionPerformed(DomaineEcrans& domaine, int dx, int dy);

    private :
	GLImages* ptrGLImage;
    };

#endif
