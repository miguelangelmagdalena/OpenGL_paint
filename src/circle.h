#ifndef circle_H
#define circle_H
#include "figure.h"

class circle: public figure{
	public:
	circle(float red, float green, float blue, GLfloat size, bool fill, GLfloat size_background, float red2, float green2, float blue2, int widht, int height);
	circle(float red, float green, float blue, GLfloat size, bool fill, GLfloat size_background, float red2, float green2, float blue2, int widht, int height, 
		   double	x1, double x2, double y1,double y2,double  x3,double y3);
	void drawcircle(double x0, double y0, double radius);
	void view ();
	bool selection(double x, double y);
	void view_bounding();
};

#endif