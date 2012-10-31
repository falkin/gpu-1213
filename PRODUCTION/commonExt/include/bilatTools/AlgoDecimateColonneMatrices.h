#ifndef ALGO_DECIMATE_COLONNE_MATRICES_H
#define ALGO_DECIMATE_COLONNE_MATRICES_H

#include "envTools.h"
#include "Matrices.h"

class CBI_TOOLS AlgoDecimateColonneMatrices
    {
    public:
	AlgoDecimateColonneMatrices(Matrices* ptrMatriceInput,int taille,int recouvrement);
	Matrices* run();
	virtual ~AlgoDecimateColonneMatrices();
    private :
	float moyenne(float* tabValue,int count);
	void decimateColonneOfMatrice(Matrices* ptrMatriceDecimated, int j);
	float* decimateLineOfMatrice(float* ptrLigne,int& size);

	int sizeLigneDecimate();
	int sizeColonneDecimate();
    private:
	int taille;
	int recouvrement;
	Matrices* ptrMatriceInput;
    };

#endif /* ALGODECIMATECOLONNEMATRICES_H */
