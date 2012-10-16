#ifndef IMAGE_FONCTIONEL_SELECTION_MOOS_A_H
#define IMAGE_FONCTIONEL_SELECTION_MOOS_A_H

#include "ImageMOOs.h"
#include "DomaineMaths.h"

#include <stack>
using std::stack;

/**
 * ImageMOO with a Mathematical Domaine. This domaine can be modified.
 * An history of modification is maintained for undo.
 */
class CBI_GLIMAGE ImageFonctionelMOOs_A: public ImageMOOs
    {
    public:

	ImageFonctionelMOOs_A(unsigned int m, unsigned int n, DomaineMaths domaine);

	ImageFonctionelMOOs_A(unsigned int m, unsigned int n, unsigned char* tabPixel, DomaineMaths domaine);

	ImageFonctionelMOOs_A(const ImageFonctionelMOOs_A &imageSource);

	virtual ~ImageFonctionelMOOs_A();

	void restoreFromDomaineHistory(); //Last Domaine push in History

	void headOfDomaineHistory(); //First Domaine of History

	DomaineMaths getCurrentDomaine(); //Domaine currently used

	void setCurrentDomaine(DomaineMaths domaineNew);
    protected:
	virtual void fillImage(const DomaineMaths& domaineMath)=0;
	/**
	 * New mathematical domaine for this image.
	 * Previous domaine will be put in history and current domaine is domaineNew
	 */
	virtual void onDomaineChangePerformed(const DomaineMaths& domaineNew);
    private:

	stack<DomaineMaths> stackHistoryDomaine;
    };

#endif
