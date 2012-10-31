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

	virtual void fillImage(const DomaineMaths& domaineMath)=0;

	/**
	 * Call automaticly fillImage with current domaine !
	 */
	virtual void animationStepAPI(bool& isNeedUpdateView);

	void restoreFromDomaineHistory(bool isNeedFillImage=false); //Last Domaine push in History
	void headOfDomaineHistory(bool isNeedFillImage=false); //First Domaine of History
	DomaineMaths getCurrentDomaine() const; //Domaine currently used
	void setCurrentDomaine(DomaineMaths domaineNew,bool isNeedFillImage=false);

	virtual void print(ostream& stream) const;

	void toXY(int i,int j,float& x,float& y);

    protected:
	/**
	 * New mathematical domaine for this image.
	 * Previous domaine will be put in history and current domaine is domaineNew
	 */
	virtual void onDomaineChangePerformed(const DomaineMaths& domaineNew);
    private:
	void computeDxDy();

	stack<DomaineMaths> stackHistoryDomaine;
	float dx;
	float dy;

    };

#endif
