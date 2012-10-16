#ifndef LINE_2DS_H
#define LINE_2DS_H

#include "Primitives_A.h"

class Line2Ds : public Primitives_A
    {
    public:
	Line2Ds(int x1,int y1,int x2,int y2);
	Line2Ds(const Line2Ds& source);
	virtual ~Line2Ds();

	void accept(PrimitiveVisitors_I &visitor);

    public :
	int x1;
	int y1;
	int x2;
	int y2;
    };

#endif
