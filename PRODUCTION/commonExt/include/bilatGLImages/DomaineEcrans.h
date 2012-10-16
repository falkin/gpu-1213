
#ifndef DOMAINE_ECRANS_H
#define DOMAINE_ECRANS_H

#include "envGLImage.h"
#include <string>
using std::string;

class CBI_GLIMAGE DomaineEcrans
    {
    public:
	DomaineEcrans(int x=0, int y=0, int dx=1, int dy=1);
	DomaineEcrans(const DomaineEcrans &domaineSource);

	virtual ~DomaineEcrans();

	string toString();

	int x0;
	int y0;
	int dx;
	int dy;
    };

#endif
