#ifndef ALGO_DECIMATE_COLONNE_MATRICES_H
#define ALGO_DECIMATE_COLONNE_MATRICES_H

#include "envTools.h"
#include "Matrices.h"

class CBI_TOOLS AlgoDecimateLigneMatrices
    {
    public:
	AlgoDecimateLigneMatrices(Matrices* ptrMatriceInput,int taille,int recouvrement);
	Matrices* run();
	virtual ~AlgoDecimateLigneMatrices();
    private :
	float moyenne(float* tabValue,int count);
	void decimateLingeOfMatrice(Matrices* ptrMatriceDecimated,int i);

	float* decimateLineOfMatrice(float* ptrLigne,int& size);

	int sizeLigneDecimate();
	int sizeColonneDecimate();
    private:
	int taille;
	int recouvrement;
	Matrices* ptrMatriceInput;
    };

#endif /* ALGODECIMATECOLONNEMATRICES_H */
