#include "ImageMOOs.h"

class RipplingMOO: public ImageMOOs
    {
    public:
	RipplingMOO(unsigned int w, unsigned int h, float tsStart = 0, float dt = 1);
	virtual ~RipplingMOO();
	void animationStep(bool& isNeedUpdateView);

    private:
	void fillImage(float t);
	void setPixel(int i, int j, float t);
	unsigned char computeColor(int i, int j, float t, int w, int h);

	float t;
	float dt;
    };
