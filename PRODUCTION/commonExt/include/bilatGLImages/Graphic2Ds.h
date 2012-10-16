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
	Primitives_A* popPrimitive();
	Colorf popColor();

	void reshape(int width, int height);
	void drawPrimitive(Primitives_A* primitive);
	void setColor(Colorf colorf);
	void setColor(float red, float green, float blue, float alpha = 0.0f);

	void drawLigne(int x1, int y1, int x2,int y2);
	void drawVerticalLigne(int x, int y, int height);
	void drawHorizontalLigne(int x, int y, int width);
	void drawText(int x, int y, string texte, Fonts font = Fonts::BITMAP_15);
	void drawTitleTop(string texte, Fonts font = Fonts::BITMAP_15);
	void drawTitleMiddle(string texte, Fonts font = Fonts::BITMAP_15);
	void drawTitleBottom(string texte, Fonts font = Fonts::BITMAP_15);
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
