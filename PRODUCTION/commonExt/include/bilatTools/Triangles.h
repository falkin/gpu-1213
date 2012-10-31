#ifndef TRIANGLES_H
#define TRIANGLES_H

#include "envTools.h"
#include <math.h>

#define A 0
#define B 1
#define C 2

class CBI_TOOLS Triangles
    {
    public:
	Triangles(unsigned int a=0,unsigned int b=0,unsigned int c=0);
	virtual ~Triangles();

	unsigned int getA() const;
	unsigned int getB() const;
	unsigned int getC() const;

	void setA(unsigned a);
	void setB(unsigned a);
	void setC(unsigned a);

	static float* computeNormal(float* &a,float* &b,float* &c);

    private:
	unsigned int indiceSommet[];
    };

#endif /* TRIANGLES_H */
