#ifndef FONTS_H
#define FONTS_H

#include "envGLTools.h"
#include "GLConfig.h"
#include <string>
using std::string;

class CBI_GLTOOLS Fonts
    {
    public:
	/**
	 * fontWidth and fontHeight in pixels
	 *
	 * glutFont :
	 *
	 * 	GLUT_BITMAP_8_BY_13, 8x13 pixels
	 * 	GLUT_BITMAP_9_BY_15, 9x15 pixels
	 * 	GLUT_BITMAP_TIMES_ROMAN_10
	 * 	GLUT_BITMAP_TIMES_ROMAN_24
	 * 	GLUT_BITMAP_HELVETICA_10
	 * 	GLUT_BITMAP_HELVETICA_12
	 * 	GLUT_BITMAP_HELVETICA_18
	 */
	Fonts(void* glutFont);
	Fonts(const Fonts& source);
	Fonts();
	virtual ~Fonts();
	/**
	 * compute the length in pixel of the texte
	 * if texte is multiline, return the max length of lines.
	 */
	int getWidth(string texte) const;
	int getHeight() const;
	void* getGlutFont() const;

	static  Fonts BITMAP_13();
	static  Fonts BITMAP_15();
	static  Fonts TIMES_ROMAN_10();
	static  Fonts TIMES_ROMAN_24();
	static  Fonts HELVETICA_10();
	static  Fonts HELVETICA_12();
	static  Fonts HELVETICA_18();

    private:
	void* glutFont;

	static const Fonts FONT_BITMAP_13;
	static const Fonts FONT_BITMAP_15;
	static const Fonts FONT_TIMES_ROMAN_10;
	static const Fonts FONT_TIMES_ROMAN_24;
	static const Fonts FONT_HELVETICA_10;
	static const Fonts FONT_HELVETICA_12;
	static const Fonts FONT_HELVETICA_18;
    };

#endif
