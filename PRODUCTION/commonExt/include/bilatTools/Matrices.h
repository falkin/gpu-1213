#ifndef MATRICES_H
#define MATRICES_H

#include "envTools.h"
#include <string>
#include "MinMaxs.h"
using std::string;

class CBI_TOOLS Matrices
    {
    public:
	/*
	 * Matrice n x m using data
	 * n lignes
	 * m colonnes
	 */
	Matrices(float* data, unsigned int n, unsigned int m);

	/*
	 * empyte Matrice n x m
	 * n lignes
	 * m colonnes
	 */
	Matrices(unsigned int n, unsigned int m);

	Matrices(const Matrices& source);

	/**
	 * delete data !
	 */
	virtual ~Matrices();

	void afficher();
	/*
	 * i [1,n]
	 * j [1,m]
	 * s [1,n*m]
	 */
	unsigned int indice1D(unsigned int i, unsigned int j) const;

	/**
	 * fill minMax :
	 *   minMax[0] = min value
	 *   minMax[1] = max value
	 */
	void computeMinMax();

	/*
	 * minMax[1]
	 */
	float getMax() const;

	/*
	 * minMax[0]
	 */
	float getMin() const;

	/*
	 * compute argmax for each line of the matrix
	 */
	int* computeMaxPerLine();

	/*
	 * i [1,n]
	 * j [1,m]
	 */
	float get(unsigned int i, unsigned int j) const;

	float* getLigne(unsigned int i) const;

	float* getColonne(unsigned int j) const;

	/*
	 * s [1,n*m]
	 */
	float get(unsigned int s) const;

	unsigned int getN() const;
	unsigned int getM() const;

	/**
	 * data Size = n*m
	 */
	unsigned int getDataSize();

	float* getData();

	/*
	 * i [1,n]
	 * j [1,m]
	 */
	void set(unsigned int i, unsigned int j, float value);
	/*
	 * s [1,n*m]
	 */
	void set(unsigned int s, float value);

	void setIdentity();

	static bool isEgal(Matrices* m1,Matrices* m2, float epsilon = 1e-6);
	static bool isEgal(float* ptrTabMatrice1,float* ptrTabMatrice2,int n,int m, float epsilon = 1e-6);
	static bool isEgalStats(Matrices* m1,Matrices* m2, float epsilon = 1e-6);
	static bool isEgalStats(float* ptrTabMatrice1,float* ptrTabMatrice2,int n,int m, float epsilon = 1e-6);
	static bool isEgal(float a,float b,float epsilon=1e-6);
    private:
	float* data;
	MinMaxs minMax;
	unsigned int n;
	unsigned int m;
	//Tools
	bool isNeedToDeleteData;
    };

#endif /* MATRICES_H */
