#ifndef IMAGE_VIEWERS_H
#define IMAGE_VIEWERS_H

#include "GUIEvents_I.h"
#include "GLUTWindowManagers.h"
#include "GLImageFonctionelSelections.h"

class CBI_GLIMAGE ImageViewers: public GUIEvents_I
    {
    public:

	ImageViewers(ImageMOOs* ptrImageMOO,bool useAnimation=false,bool useSelection=false, int pxFrame = 0, int pyFrame = 0);
	ImageViewers(ImageFonctionelMOOs_A* ptrImageFonctionel,bool useAnimation=false,bool useSelection=true, int pxFrame = 0, int pyFrame = 0);
	virtual ~ImageViewers();

	GLImageAPIWindows* getGLImageWindow();

	void updateView();

	static void init(int argc,char** argv);

	/**
	 * Attention appel bloquant !
	 */
	static void runALL();
	static void runALL(FRERE_MASTER_THREAD methodeFrereMasterThread,void** param);


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

	ImageViewers(){};

    protected :
	GLImageAPIWindows* ptrGLImageWindow;
    };

#endif
