#ifndef TITLE_DRAWERS_H
#define TITLE_DRAWERS_H

#include "envGLImage.h"
#include "ImageTitles.h"
#include "Fonts.h"

#include <string>
using std::string;

class CBI_GLIMAGE TitleDrawers
    {
    public:
	TitleDrawers();
	virtual ~TitleDrawers();

	void setTitleTop(string title,float r,float g,float b,Fonts font);
	void setTitleBottom(string title,float r,float g,float b,Fonts font);
	void setTitleMiddle(string title,float r,float g,float b,Fonts font);

	void removeTitleTop();
	void removeTitleBottom();
	void removeTitleMiddle();

	void reshape(int w,int h);

	void drawTitles();
	void drawCredits();
    private:
	void drawTitleTop();
	void drawTitleMiddle();
	void drawTitleBottom();

    private :
	ImageTitles titleTop;
	ImageTitles titleMiddle;
	ImageTitles titleBottom;

	int frameWidth;
	int frameHeight;
    };


#endif
