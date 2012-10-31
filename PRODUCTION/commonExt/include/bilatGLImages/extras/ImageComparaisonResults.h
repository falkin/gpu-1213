#ifndef IMAGE_COMPARAISON_RESULTS_H
#define IMAGE_COMPARAISON_RESULTS_H

#include "envGLImage.h"

class CBI_GLIMAGE ImageComparaisonResults
    {
    public:
	ImageComparaisonResults()
	    {
	    isEgal = true;
	    nbErreur = 0;
	    deltaMax = 0;
	    deltaMin = 0;
	    }
	;

	bool isEgal;
	unsigned int deltaMax;
	unsigned int deltaMin;
	int nbErreur;

    };

#endif
