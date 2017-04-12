#ifndef line_H
#define line_H
#include "figure.h"

class line: public figure{
	public:
	line(float red, float green, float blue, GLfloat size, bool fill, GLfloat size_background, float red2, float green2, float blue2, int widht, int height);
	line(float red, float green, float blue, GLfloat size, bool fill, GLfloat size_background, float red2, float green2, float blue2, int widht, int height, 
		   double	x1, double x2, double y1,double y2,double  x3,double y3);
	void view ();
	bool selection(double x, double y);
	void view_bounding();
};

#endif