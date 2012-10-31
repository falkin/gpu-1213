#ifndef GRAPHIC2DS_H
#define GRAPHIC2DS_H

#include "envGLImage.h"
#include "Color3f.h"
#include "Primitives_A.h"
#include "Fonts.h"
#include <string>
#include <queue>

using std::queue;
using std::string;

class CBI_GLIMAGE Graphic2Ds
    {
    public:
	Graphic2Ds(int width, int height);
	virtual ~Graphic2Ds();
	void reshape(int width, int height);

	void drawPrimitive(Primitives_A* primitive);
	Primitives_A* popPrimitive();

	Colorf popColor();
	void setColor(Colorf colorf);
	void setColorRGB(float r01, float g01, float b01, float a01 = 1.0f);
	void setColorHSB(float h01, float s01, float b01, float a01 = 1.0f);

	void drawLigne(int x1, int y1, int x2,int y2);
	void drawVerticalLigne(int x, int y, int height);
	void drawHorizontalLigne(int x, int y, int width);
	void drawText(int x, int y, string texte, Fonts font=Fonts::HELVETICA_12());
	void drawTitleTop(string texte, Fonts font=Fonts::HELVETICA_12());
	void drawTitleMiddle(string texte, Fonts font=Fonts::HELVETICA_12());
	void drawTitleBottom(string texte, Fonts font=Fonts::HELVETICA_12());
	void drawWiredRect2D(int x, int y, int width, int height);
	void drawRect2D(int x, int y, int width, int height);

	int texteWidth(string texte,Fonts font);
	int texteHeight(string texte,Fonts font);

	unsigned int getSize();
	bool isEmpty();

    private:
	Colorf currentColor;
	queue<Colorf> queueColors;
	queue<Primitives_A*> queuePrimitives;
	int width;
	int height;
	int frameWidth;
	int frameHeight;
    };

#endif
