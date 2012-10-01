
#ifndef IMAGETITLES_H
#define IMAGETITLES_H

#include "envGLImage.h"
#include "Fonts.h"

#include <string>
using std::string;

class CBI_GLIMAGE ImageTitles
    {
    public:
	ImageTitles(string texte,float r,float v,float b,Fonts font);
	ImageTitles(const ImageTitles& source);
	virtual ~ImageTitles();

	string getTexte() const;
	float* getColor() const;
	Fonts getFont() const;

	void setTexte(string texte);
	void setColor(float r,float v,float b);
	void setFont(Fonts font);
    private :
	string texte;
	float* color; //RVB
	Fonts font;
    };

#endif
