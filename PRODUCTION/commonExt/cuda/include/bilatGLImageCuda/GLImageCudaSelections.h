#ifndef GLIMAGE_CUDAS_ELECTIONS_H
#define GLIMAGE_CUDA_SELECTIONS_H

#include "GLImageCudas.h"

#include "DomaineEcrans.h"


class CBI_GLIMAGE_CUDA GLImageCudaSelections : public GLImageCudas
    {
    public:
	GLImageCudaSelections(ImageCudaMOOs_A* ptrImageCudaMOO,bool isAnimationEnable = true, int pxFrame = 0, int pyFrame = 0);
	virtual ~GLImageCudaSelections();



    protected :

	/**
	 * then selection is performed with the mouse,
	 * domaine in frame coordinate
	 **/
	virtual void selectionPerformed(const DomaineEcrans& domaineEcran,int dxFrame,int dyFrame);

	DomaineEcrans getCurrentDomaineSelection() const;

    private:

	void display();
	void mouseMoved(int x, int y);
	void mousePressed(int button, int state, int x, int y);
	void drawSelection();

    private:
	DomaineEcrans domaineSelection;
	bool isSelectionEnable;
	float ratio; //ration de la taille de la selection proportionnel à l'image
    };

#endif
