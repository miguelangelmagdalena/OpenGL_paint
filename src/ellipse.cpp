#include "figure.h"
#include "ellipse.h"

ellipse::ellipse(float red, float green, float blue, GLfloat size, bool fill, GLfloat size_background, float red2, float green2, float blue2, int widht, int height){
	option = 4;
	color_border.color[0]	= red;
	color_border.color[1]	= green;
	color_border.color[2]	= blue;
	size_border				= size;
	fill_up					= fill;
	size_background	= size_background;
	color_background.color[0]	= red2;
	color_background.color[1]	= green2;
	color_background.color[2]	= blue2;
	interval_bounding_box	= size_border + 3;
	selected = false;
	SCREEN_WIDTH = widht;
	SCREEN_HEIGHT = height;
};
ellipse::ellipse(float red, float green, float blue, GLfloat size, bool fill, GLfloat size_background, float red2, float green2, float blue2, int widht, int height, 
		   double	x1, double x2, double y1,double y2,double  x3,double y3){
	option = 1;
	color_border.color[0]	= red;
	color_border.color[1]	= green;
	color_border.color[2]	= blue;
	size_border				= size;
	fill_up					= fill;
	//size_background	= size_background;
	color_background.color[0]	= red2;
	color_background.color[1]	= green2;
	color_background.color[2]	= blue2;
	interval_bounding_box	= size_border + 3;
	selected = false;
	SCREEN_WIDTH = widht;
	SCREEN_HEIGHT = height;

	this->x1 = x1;
	this->x2 = x2;
	this->x3 = x3;
	this->y1 = y1;
	this->y2 = y2;
	this->y3 = y3;
};	
void ellipse::ellipse_points(double xc, double yc, double x, double y){
	if(fill_up){
		horizontal_line(xc-x+size_border-2, yc+y-size_border, xc+x-size_border+2);
		horizontal_line(xc-x+size_border-2, yc-y+size_border, xc+x-size_border+2);

	}
	put_pixel(xc+x, yc+y, color_border, size_border);
	put_pixel(xc-x, yc+y, color_border, size_border);
	put_pixel(xc+x, yc-y, color_border, size_border);
	put_pixel(xc-x, yc-y, color_border, size_border);
};
void ellipse::ellipse_midpoint(double xc, double yc, double rx, double ry)
{
    double rxSq = rx * rx;
    double rySq = ry * ry;
    double	x = 0, 
			y = ry, 
			p;
    double	px = 0, 
			py = 2 * rxSq * y;

	// Dibuja 4 puntos simétricos de la elipse

    ellipse_points(xc, yc, x, y);

    // Modalidad 1
    p = rySq - (rxSq * ry) + (0.25 * rxSq);
    while (px < py)
    {
       
        px = px + 2 * rySq;
        if (p < 0)
            p = p + rySq + px;
        else
        {
            py = py - 2 * rxSq;
            p = p + rySq + px - py;
			y--;
        }
		 x++;


		
        ellipse_points(xc, yc, x, y);
    }

    // Modalidad 2
    p = rySq*(x+0.5)*(x+0.5) + rxSq*(y-1)*(y-1) - rxSq*rySq;
    while (y > 0)
    {
        
        py = py - 2 * rxSq;
        if (p > 0)
            p = p + rxSq - py;
        else
        {
            px = px + 2 * rySq;
            p = p + rxSq - py + px;
			x++;
        }
		y--;
        ellipse_points(xc, yc, x, y);
    }
};

void ellipse::view (){
	double a = x2 - x1, b = y2 - y1;
	if(b < 0) b = y1 - y2;
	if(a < 0) a = x1 - x2;

	x1_bounding = x1 - a;
	y1_bounding = y1 - b;
	x2_bounding = x1 + a;
	y2_bounding = y1 + b;

	ellipse_midpoint(x1,y1,a,b);
	if(selected)
		view_bounding();
};
bool ellipse::selection(double x, double y){
	if(inside_box(x1_bounding-interval_bounding_box, y1_bounding-interval_bounding_box, x2_bounding+interval_bounding_box,y2_bounding+interval_bounding_box, x,y) )
		return true;

	selected = false;
	return false;
}
void ellipse::view_bounding(){
	struct tipo_color color1, color2;
	color1.color[0] = 0.0; color1.color[1] = 0.0; color1.color[2] = 0.0;
	color2.color[0] = 1.0; color2.color[1] = 1.0; color2.color[2] = 1.0;

	double_linea_vertical2	(x1_bounding-interval_bounding_box,
							y1_bounding-interval_bounding_box,
							x1_bounding+interval_bounding_box,
							y2_bounding+interval_bounding_box,
							x2_bounding+interval_bounding_box,
							color1,color2,2);

	double_linea_horizontal2 (x1_bounding-interval_bounding_box,
							y1_bounding-interval_bounding_box,
							x2_bounding+interval_bounding_box,
							y1_bounding-interval_bounding_box,
							y2_bounding+interval_bounding_box,
							color1,color2,2);
}