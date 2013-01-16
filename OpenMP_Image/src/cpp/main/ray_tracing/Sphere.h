#ifndef SPHERE_H_
#define SPHERE_H_

#include <cmath>

struct float3
    {
	float x,y, z;
    };
struct float2
    {
	float x,y;
    };

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Sphere
    {
    public:
	Sphere()
	    {
	    }

	Sphere(float3 centre, float rayon, float hue)
	    {
	    this->centre = centre;
	    this->r = rayon;
	    this->rCarre = rayon * rayon;
	    this->hue = hue;
	    }

	float hCarre(float2 xySol)
	    {
	    float a = centre.x - xySol.x;
	    float b = centre.y - xySol.y;
	    return a * a + b * b;
	    }

	bool isBelow(float hCarre)
	    {
	    return hCarre < rCarre;
	    }

	float dz(float hCarre)
	    {
	    return sqrtf(rCarre - hCarre);
	    }

	float brightness(float dz)
	    {
	    return dz / r;
	    }

	float distance(float dz)
	    {
	    return centre.z - dz;
	    }

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
