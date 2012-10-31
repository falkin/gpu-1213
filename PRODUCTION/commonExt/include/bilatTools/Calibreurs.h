#ifndef CALIBREURS_H
#define CALIBREURS_H

#include "envTools.h"

class CBI_TOOLS Calibreurs
    {
    public:
	Calibreurs(float x1, float x2, float y1, float y2);
	Calibreurs(const Calibreurs& source);
	virtual ~Calibreurs();

	/**
	 * x in [x1,x2]
	 * return x' in [y1,y2]
	 */
	float calibrate(float x) const;


    private:
	//Inputs
	float x1;
	float x2;
	float y1;
	float y2;

	//Tools
	float pente;
	float t;
    };

#endif
