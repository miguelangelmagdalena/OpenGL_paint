#ifndef rectangle_H
#define rectangle_H
#include "figure.h"

class rectangle: public figure{
	public:
	rectangle(float red, float green, float blue, GLfloat size, bool fill, GLfloat size_background, float red2, float green2, float blue2, int widht, int height);
	rectangle(float red, float green, float blue, GLfloat size, bool fill, GLfloat size_background, float red2, float green2, float blue2, int widht, int height, 
		   double	x1, double x2, double y1,double y2,double  x3,double y3);
	//void linea_recta(double x0, double y0, double x1, double y1);
	void double_linea_horizontal(double x0, double y0, double x1, double y1, double y2);
	void double_linea_vertical(double x0, double y0, double x1, double y1, double x2);
	void fill_up_rectangle(double xmin, double ymin, double xmax, double ymax);
	void view ();
	bool selection(double x, double y);
	void view_bounding();
};

#endif