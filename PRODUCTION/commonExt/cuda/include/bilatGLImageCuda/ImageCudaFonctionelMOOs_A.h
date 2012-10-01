#ifndef IMAGE_CUDA_FONCTIONEL_MOOS_A_H
#define IMAGE_CUDA_FONCTIONEL_MOOS_A_H

#include "ImageCudaMOOs_A.h"
#include "DomaineMaths.h"

#include <stack>
using std::stack;

class CBI_GLIMAGE_CUDA ImageCudaFonctionelMOOs_A: public ImageCudaMOOs_A
    {
    public:
	ImageCudaFonctionelMOOs_A(unsigned int w, unsigned int h, DomaineMaths domaineMath);
	virtual ~ImageCudaFonctionelMOOs_A();

	void restoreFromDomaineHistory(); //Last Domaine push in History

	void headOfDomaineHistory(); //First Domaine of History

	DomaineMaths getCurrentDomaine(); //Domaine currently used

	void setCurrentDomaine(DomaineMaths domaineNew);

	/**
	 * w et h fixe, ne change pas au cours du temps !
	 */
	virtual void fillImageGL(uchar4* ptrDevImageGL, int w, int h, const DomaineMaths& domaineNew)=0; //ptrDevImageGL zone memoire commune OpenGL et Cuda

    protected:
	/**
	 * Call each time the domaine change
	 * 	1) Domaines : new domaine of the image
	 */
	virtual void onDomaineChangePerformed(const DomaineMaths& domaineNew);
    private:
	void fillImageGL(uchar4* ptrDevImageGL, int w, int h); //from ImageCudaMOO_A
    private:

	stack<DomaineMaths> stackHistoryDomaine;
    };

#endif
