#ifndef ellipse_H
#define ellipse_H
#include "figure.h"
class ellipse: public figure{
	public:
	ellipse(float red, float green, float blue, GLfloat size, bool fill, GLfloat size_background, float red2, float green2, float blue2, int widht, int height);
	ellipse(float red, float green, float blue, GLfloat size, bool fill, GLfloat size_background, float red2, float green2, float blue2, int widht, int height, 
		   double	x1, double x2, double y1,double y2,double  x3,double y3);
	void ellipse_midpoint(double xc, double yc, double rx, double ry);
	void ellipse_points(double xc, double yc, double x, double y);
	void view ();
	bool selection(double x, double y);
	void view_bounding();
};
#endif