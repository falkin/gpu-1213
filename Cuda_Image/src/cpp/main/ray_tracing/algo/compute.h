#ifndef COMPUTE_H_
#define COMPUTE_H_

#include "Sphere.h"
#include "ColorToolCuda.h"

#define CUDART_PI_F 3.141592654f

__device__
float hue_time_function(float t, float hue_t0)
    {
    float pi3_2 = 3 * CUDART_PI_F / 2;
    float param_t = asinf(2 * hue_t0 - 1) - pi3_2;
    return 1.0 / 2 + 1.0 / 2 * sinf(t + pi3_2 + param_t);
    }

__device__
void compute(uchar4& ptrColor, int dim, int i, int j, float t, Sphere* ptrDevSphereArray, int nbSphere)
    {
    float2 xysol =
	{
	i, j
	};
    float3 hsb =
	{
	0, 0, 0
	};
    ;
    ptrColor.x = ptrColor.y = ptrColor.z = 0;

    hsb.y = 1.0;
    for (int i = 0; i < nbSphere; i++)
	{
	float hcarre = ptrDevSphereArray[i].hCarre(xysol);
	if (ptrDevSphereArray[i].isBelow(hcarre))
	    {
	    float dz = ptrDevSphereArray[i].dz(hcarre);
	    hsb.z = ptrDevSphereArray[i].brightness(dz);
	    hsb.x = hue_time_function(t, ptrDevSphereArray[i].getHue());
	    }
	}
    ColorToolCuda::HSB_TO_RVB(hsb, ptrColor);
    ptrColor.w = 255;
    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
#endif
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
