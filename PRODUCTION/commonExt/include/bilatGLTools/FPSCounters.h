#ifndef FPS_COUNTERS_H
#define FPS_COUNTERS_H

#include "envGLTools.h"
#include <time.h>

class CBI_GLTOOLS FPSCounters
    {
    public:
	FPSCounters();

	virtual ~FPSCounters();

	void frame();

    public:
	int frameCount;
	int fps;
	time_t startTimeMs;
    };

#endif
