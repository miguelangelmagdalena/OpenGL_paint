#ifndef triangle_H
#define triangle_H
#include "figure.h"

class triangle: public figure{
	public:

	triangle(float red, float green, float blue, GLfloat size, bool fill, GLfloat size_background, float red2, float green2, float blue2, int widht, int height);
	triangle(float red, float green, float blue, GLfloat size, bool fill, GLfloat size_background, float red2, float green2, float blue2, int widht, int height, 
		   double	x1, double x2, double y1,double y2,double  x3,double y3);
	void view ();
	bool point_inside_line(int x1, int y1, int x2, int y2, int point_x, int point_y);
	bool selection(double x, double y);
	void view_bounding();
	void triangle::mayor_menor();
};

#endif