#ifndef COMPUTE_H_
#define COMPUTE_H_

#include "Sphere.h"
#include "ColorTools.h"
#include <limits>
#include <stdio.h>

#define CUDART_PI_F 3.141592654f

float hue_time_function(float t, float hue_t0)
    {
    float pi3_2 = 3 * CUDART_PI_F / 2;
    float param_t = asinf(2 * hue_t0 - 1) - pi3_2;
    return 1.0 / 2 + 1.0 / 2 * sinf(t + pi3_2 + param_t);
    }

float3 compute(int i, int j, float t, Sphere* ptrDevSphereArray, int nbSphere)
    {
    float2 xysol =
	{
	i, j
	};
    float3 hsb =
	{
	0, 0, 0
	};
    float ptrColo =


    hsb.y = 1.0;
    float minDistance =  std::numeric_limits<float>::infinity();

    int indexMin = -1;
    for (int i = 0; i < nbSphere; i++)
	{
	Sphere* sphere = &ptrDevSphereArray[i];
	float hcarre = sphere->hCarre(xysol);
	float dz = sphere->dz(hcarre);
	if (sphere->isBelow(hcarre) && sphere->distance(dz) < minDistance)
	    {
	    minDistance = sphere->distance(dz);
	    indexMin = i;
	    }
	}
    if (indexMin != -1)
	{
	float hcarre = ptrDevSphereArray[indexMin].hCarre(xysol);
	float dz = ptrDevSphereArray[indexMin].dz(hcarre);
	hsb.z = ptrDevSphereArray[indexMin].brightness(dz);
	hsb.x = hue_time_function(t, ptrDevSphereArray[indexMin].getHue());

	}


    return hsb;

    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
#endif
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
