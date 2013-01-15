#ifndef IMAGECUDA_H
#define IMAGECUDA_H

#include "ImageMOOs.h"
#include "Sphere.h"

class RayTracingImageCudaMOO: public ImageMOOs
    {
    public:
	RayTracingImageCudaMOO(unsigned int w, unsigned int h, float tsStart = 0, float dt = 1, int nbSphere = 10);
	virtual ~RayTracingImageCudaMOO();
	void animationStep(bool& isNeedUpdateView);

    private:
	void fillImageGL();
	void setPixel(int i, int j, float t);
	unsigned char computeColor(int i, int j, float t, int w, int h);

	float t;
	float dt;
	Sphere* ptrHostSphereArray;
	int nbSphere;
    };

#endif
