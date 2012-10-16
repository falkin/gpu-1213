#ifndef ALGO_DECIMATE_3D_COLONNE_MATRICES_H
#define ALGO_DECIMATE_3D_COLONNE_MATRICES_H

#include "envTools.h"
#include "Matrices.h"
#include <vector>

using std::vector;

class CBI_TOOLS AlgoDecimate3DColonneMatrices
    {
    public:
	AlgoDecimate3DColonneMatrices(Matrices* ptrMatriceInput, int taille, int recouvrement, int rayon);
	Matrices* run();
	virtual ~AlgoDecimate3DColonneMatrices();
    private:
	float moyenne(vector<float*>, int count);
	/*void decimateLingeOfMatrice(Matrices* ptrMatriceDecimated,int i);*/
	void decimateColonneOfMatrice(Matrices* ptrMatriceDecimated, int j);
	float* computeSubColonneToDecimate(int i, int j);
	/*float* decimateLineOfMatrice(float* ptrLigne,int& size);*/

	int sizeLigneDecimate();
	int sizeColonneDecimate();
    private:
	int taille;
	int recouvrement;
	int rayon;
	Matrices* ptrMatriceInput;
    };

#endif
