#ifndef COLOR_F_H
#define COLOR_F_H
#include "envGLTools.h"

class CBI_GLTOOLS Colorf
    {
    public:
	Colorf(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
	virtual ~Colorf();

    public:
	float r;
	float g;
	float b;
	float a;

	static Colorf RED;
	static Colorf BLUE;
	static Colorf GREEN;
	static Colorf YELLOW;
	static Colorf MANGANTA;
	static Colorf CYAN;
	static Colorf WHITE;
    };

#endif
