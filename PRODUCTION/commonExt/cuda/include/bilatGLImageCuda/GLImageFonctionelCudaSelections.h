#ifndef GLIMAGE_FONCTIONEL_CUDA_SELECTIONS_H
#define GLIMAGE_FONCTIONEL_CUDA_SELECTIONS_H

#include "GLImageCudaSelections.h"
#include "ImageCudaFonctionelMOOs_A.h"

#define KEY_HEAD_DOMAINE_HISTORY GLUT_KEY_HOME
#define KEY_RESTORE_DOMAINE 8 //code ascii for Backspace

class CBI_GLIMAGE_CUDA GLImageFonctionelCudaSelections: public GLImageCudaSelections
    {
    public:
	GLImageFonctionelCudaSelections(ImageCudaFonctionelMOOs_A* ptrImageCudaFonctionelMOO, bool isAnimationEnable = true,int pxFrame = 0, int pyFrame = 0);
	virtual ~GLImageFonctionelCudaSelections();

	ImageCudaFonctionelMOOs_A* getPtrImageCudaFonctionelMOO();


    protected:

	/**
	 * then selection is performed with the mouse, 3 arguments :
	 *	1) selected domaine in frame coordinate
	 *	2) dx is the screen width in pixLa clel
	 *	3) dy is the screen height in pixel
	 **/
	void selectionPerformed(const DomaineEcrans& domaineEcran, int dx, int dy);
    private:
	void keyPressed(unsigned char key, int x, int y);
	void specialKeyPressed(int key, int x, int y);

    };

#endif
