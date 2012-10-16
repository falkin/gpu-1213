#ifndef COURBE_MOOS_A_H
#define COURBE_MOOS_A_H

#include "envTools.h"
#include "Domaine22s.h"

class CBI_TOOLS Courbe2DMOOs
    {
    public:
	Courbe2DMOOs(unsigned int vertexCount);
	virtual ~Courbe2DMOOs();

	void setVertex(unsigned int i, float x, float y);

	unsigned int getVertexCount() const;
	unsigned int getTabVertexSizeOctet() const;
	float* getTabVertices();

	float getXi(int i);
	float getYi(int i);
	void getVertex(int i, float &x, float &y);
	Domaine22s getDomaine22();

	Domaine22s computeDomaine22();

    private:
	float* ptrTabVertices;
	unsigned int vertexCount;
	Domaine22s domaine22;
    };

#endif
