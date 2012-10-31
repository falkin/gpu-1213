#ifndef DOMAINE_MATHS_H
#define DOMAINE_MATHS_H

#include "envGLImage.h"
#include "DomaineEcrans.h"
#include <string>

using std::string;
using std::ostream;

/**
 * (x0,y0) upper left corner of a dx x dy square.
 */
class CBI_GLIMAGE DomaineMaths
    {
    public:

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

	DomaineMaths();

	DomaineMaths(float x0, float y0, float x1, float y1);

	DomaineMaths(const DomaineMaths &domaineSource);

	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/

	virtual ~DomaineMaths();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

	DomaineMaths extractDomaineFromSelection(const DomaineEcrans &domaineSelection, int dxFrame, int dyFrame);

	string toString();

	inline float dx() const
	    {
	    return x1 - x0;
	    }

	inline float dy() const
	    {
	    return y1 - y0;
	    }

	static DomaineMaths create(float x0, float y0, float dx, float dy);

	/*--------------------------------------*\
	 |*		Friend			*|
	 \*-------------------------------------*/

	CBI_GLIMAGE friend ostream& operator<<(ostream& stream, const DomaineMaths& domaine);

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

	float x0;
	float y0;
	float x1;
	float y1;
    };



#endif
