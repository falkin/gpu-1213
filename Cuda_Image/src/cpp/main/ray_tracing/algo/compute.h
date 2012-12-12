#ifndef COMPUTE_H_
#define COMPUTE_H_

#include "Sphere.h"
#include "ColorToolCuda.h"

__device__
void compute ( uchar4& ptrColor, int dim, int i, int j, float t ,Sphere* ptrDevSphereArray, int nbSphere) {
  float2 xysol={i,j};
  float3 hsb = {0,0,0};
  hsb.x=50;
  hsb.y=1;
  ptrColor.x = ptrColor.y = ptrColor.z = 0;
  for(int i=0;i<nbSphere;i++){
      float hcarre = ptrDevSphereArray[i].hCarre(xysol);
      if(ptrDevSphereArray[i].isBelow(hcarre)) {
	  float dz = ptrDevSphereArray[i].dz(hcarre);
	  hsb.z=ptrDevSphereArray[i].brightness(dz);
      }
  }
  ColorToolCuda::HSB_TO_RVB(hsb,ptrColor);
  ptrColor.w = 255;
}
/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
#endif
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
