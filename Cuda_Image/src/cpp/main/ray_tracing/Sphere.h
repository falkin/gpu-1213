#ifndef SPHERE_H_
#define SPHERE_H_

#include "cudaTools.h"
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Sphere
    {
    public:
	__host__
	Sphere(){}

	__host__
	Sphere(float3 centre, float rayon, float hue){
	this->centre= centre;
	this->r=rayon;
	this->rCarre=rayon*rayon;
	this->hue=hue;
	}

	__device__
	float hCarre(float2 xySol)
	    {
	    float a= centre.x - xySol.x;
	    float b = centre.y - xySol.y;
	    return a*a+b*b;
	    }

	__device__
	bool isBelow(float hCarre)
	    {
	    return hCarre < rCarre;
	    }

	__device__
	float dz(float hCarre)
	    {
	    return sqrtf(rCarre-hCarre);
	    }

	__device__
	float brightness(float dz)
	    {
	    return dz/r;
	    }

	__device__
	float distance(float dz)
	    {
	    return centre.z-dz;
	    }

	__device__
	float getHue()
	    {
	    return hue;
	    }

    private:
	float rCarre;
	float r;
	float3 centre;
	float hue;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
