#ifndef DOMAINE22S_H
#define DOMAINE22S_H

#include "MinMaxs.h"

class CBI_TOOLS Domaine22s
    {
    public:
	Domaine22s(float xMin,float xMax,float yMin,float yMax);
	Domaine22s(MinMaxs intervalX,MinMaxs intervalY);
	Domaine22s(const Domaine22s &source);
	virtual ~Domaine22s();

	MinMaxs getIntervalX();
	MinMaxs getIntervalY();

	static Domaine22s computeDomaine(float* tabVertex,unsigned int nbVertex);

    private :
	MinMaxs intervalX;
	MinMaxs intervalY;
    };

#endif
