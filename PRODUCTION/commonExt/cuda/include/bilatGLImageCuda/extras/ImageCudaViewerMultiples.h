#ifndef IMAGE_CUDA_VIEWER_MULTIPLES_H
#define IMAGE_CUDA_VIEWER_MULTIPLES_H

#include "GUIEvents_I.h"
#include "GLImageFonctionelCudaSelections.h"
#include "Fonts.h"

class CBI_GLIMAGE_CUDA ImageCudaViewerMultiples: public GUIEvents_I
    {
    public:
	ImageCudaViewerMultiples(ImageCudaMOOs_A* ptrImageCudaMOO, bool useAnimation = true, bool useSelection = false, int pxFrame = 0, int pyFrame = 0);
	ImageCudaViewerMultiples(ImageCudaFonctionelMOOs_A* ptrImageCudaFonctionel, bool useAnimation = true, bool useSelection = true, int pxFrame = 0,
		int pyFrame = 0);
	virtual ~ImageCudaViewerMultiples();

	GLImageCudas* getGLImage();

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
	 *	2) dx is the screen width in pixLa clel
	 *	3) dy is the screen height in pixel
	 **/
	virtual void selectionPerformed(DomaineEcrans& domaine, int dx, int dy);

    private:
	GLImageCudas* ptrGLImage;
    };

#endif
