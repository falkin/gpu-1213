#ifndef STATE_EGALITE_H
#define STATE_EGALITE_H

#include "envGLImage.h"

class CBI_GLIMAGE StateEgalite
    {
    public:
	StateEgalite()
	    {
	    isEgal = true;
	    nbErreur = 0;
	    deltaMax = 0;
	    deltaMin = 0;
	    }
	;
	virtual ~StateEgalite()
	    {
	    }
	;
    public:
	bool isEgal;
	float deltaMax;
	float deltaMin;
	int nbErreur;

    };

#endif
