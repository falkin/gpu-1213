
#ifndef MINMAXS_H
#define MINMAXS_H

#include "envTools.h"

class CBI_TOOLS MinMaxs
    {
    public:
	MinMaxs(float vMin=0,float vMax=1);
	MinMaxs(const MinMaxs& source);
	virtual ~MinMaxs();

	static MinMaxs computeMinMax(float* ptrValues,int n);

	float delta();
	float deltaAbs();

	float getMin() const;
	float getMax() const;

    private :
	float vMin;
	float vMax;
    };

#endif /* MINMAXS_H_ */
