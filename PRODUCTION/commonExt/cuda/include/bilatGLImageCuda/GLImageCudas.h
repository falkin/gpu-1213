#ifndef GLIMAGE_CUDAS_H
#define GLIMAGE_CUDAS_H

#include "envGLImageCudas.h"
#include "GLImageAPIWindows.h"
#include "CudaInteropTools.h"
#include "TitleDrawers.h"
#include "ImageCudaMOOs_A.h"

/**
 * Data plus stocker in Central Memory, mais in GPU memory !
 */
class CBI_GLIMAGE_CUDA GLImageCudas: public GLImageAPIWindows
    {
    public:

	/**
	 *   (dx,dy)		:  Size of the image
	 *   (pxFrame,pyFrame) 	:  The position of the upper left corner of the frame in screen space.
	 */
	GLImageCudas(ImageCudaMOOs_A* ptrImageCudaMOO, bool isAnimationEnable = true,int pxFrame = 0, int pyFrame = 0);

	virtual ~GLImageCudas();

	ImageCudaMOOs_A* getPtrImageCudaMOO();

    protected:
	/**
	 * Fonction appel� a chaque fois que glut n'a rien � faire dans la mainLoop.
	 * C�D s'il n'y a pas d'�venents utilisateur (souris,clavier,joystick,repaint,etc...)
	 */
	virtual void idleFunc();

	 void createPBO();
	 void fillPBO();

    private:
	//Inputs
	ImageCudaMOOs_A* ptrImageCudaMOO;

	//Cuda interop
	cudaGraphicsResource* cudaRessource;
    };

#endif
