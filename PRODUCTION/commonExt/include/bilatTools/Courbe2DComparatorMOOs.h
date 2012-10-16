#ifndef COURBETESTALGOVISUELMOOS_H
#define COURBETESTALGOVISUELMOOS_H

#include "envTools.h"
#include "Courbe2DMOOs.h"

class CBI_TOOLS Courbe2DComparatorMOOs: public Courbe2DMOOs
    {
    public:
	Courbe2DComparatorMOOs(float* ptrDataSource,float* ptrDataTheorique,unsigned int nbElement);
	virtual ~Courbe2DComparatorMOOs();
	virtual void update();
	void setDataSource(float* ptrDataSource);
	void setDataTheorique(float* ptrDataTheorique);
    private :
	void fillVertex();
    private :
	float* ptrDataSource;
	float* ptrDataTheorique;
    };

#endif
