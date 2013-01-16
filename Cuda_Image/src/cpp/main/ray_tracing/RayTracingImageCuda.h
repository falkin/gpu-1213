#ifndef IMAGECUDA_H
#define IMAGECUDA_H

#include "ImageCudaMOOs_A.h"
#include "Sphere.h"

class RayTracingImageCudaMOO: public ImageCudaMOOs_A
    {
    public:
	RayTracingImageCudaMOO(unsigned int w, unsigned int h, float tsStart = 0, float dt = 1, int nbSphere = 10, MemType memType = GLOBAL, dim3 dg = dim3(16,1,1), dim3 db = dim3(32,1,1));
	virtual ~RayTracingImageCudaMOO();
	void animationStep(bool& isNeedUpdateView);

    public:
	void fillImageGL(uchar4* ptrDevImageGL, int w, int h);
	void setPixel(int i, int j, float t);
	unsigned char computeColor(int i, int j, float t, int w, int h);

	float t;
	float dt;
	Sphere* ptrHostSphereArray;
	Sphere* ptrDevSphereArray;
	int nbSphere;
	MemType memType;
	dim3 dg,db;
    };

#endif
