#ifndef TEXT2DS_H
#define TEXT2DS_H

#include "Primitives_A.h"
#include "Fonts.h"

#include <string>
using std::string;

class CBI_GLIMAGE Text2Ds : public Primitives_A
    {
    public:
	Text2Ds(int x,int y,string texte,Fonts font=Fonts::HELVETICA_10());
	virtual ~Text2Ds();
	void accept(PrimitiveVisitors_I &visitor);

    public:
	string texte;
	Fonts font;
	int x;
	int y;
    };

#endif
