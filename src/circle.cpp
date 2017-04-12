#include "figure.h"
#include "circle.h"


//#include <iostream>
circle::circle(float red, float green, float blue, GLfloat size, bool fill, GLfloat size_background, float red2, float green2, float blue2, int widht, int height){
	option = 2;
	color_border.color[0]	= red;
	color_border.color[1]	= green;
	color_border.color[2]	= blue;
	size_border				= size;
	fill_up					= fill;
	//size_background			= size_background;
	color_background.color[0]	= red2;
	color_background.color[1]	= green2;
	color_background.color[2]	= blue2;
	interval_bounding_box	= size_border + 3;
	selected = false;
	SCREEN_WIDTH = widht;
	SCREEN_HEIGHT = height;
};
circle::circle(float red, float green, float blue, GLfloat size, bool fill, GLfloat size_background, float red2, float green2, float blue2, int widht, int height, 
		   double	x1, double x2, double y1,double y2,double  x3,double y3){
	option = 1;
	color_border.color[0]	= red;
	color_border.color[1]	= green;
	color_border.color[2]	= blue;
	size_border				= size;
	fill_up					= fill;
	size_background			= size_background;
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
void circle::drawcircle(double x0, double y0, double radius)
{
	double x = radius;
	double y = 0;
	double err = 0;

	

	while (x >= y)
	{
		
		if(fill_up){
			horizontal_line(x0-x+size_border-1, y0+y-size_border, x0+x-size_border);
			horizontal_line(x0-y+size_border-1, y0+x-size_border, x0+y-size_border);
			horizontal_line(x0-y+size_border-1, y0-x+size_border, x0+y-size_border);
			horizontal_line(x0-x+size_border-1, y0-y+size_border, x0+x-size_border);
			/*horizontal_line(x0-x, y0+y-size_border, x0+x);
			horizontal_line(x0-y, y0+x-size_border, x0+y);
			horizontal_line(x0-y, y0-x+size_border, x0+y);
			horizontal_line(x0-x, y0-y+size_border, x0+x);*/
		}

		//Dibuja 8 puntos
		put_pixel(x0 + x, y0 + y, color_border, size_border);
		put_pixel(x0 + y, y0 + x, color_border, size_border);
		put_pixel(x0 - y, y0 + x, color_border, size_border);
		put_pixel(x0 - x, y0 + y, color_border, size_border);
		put_pixel(x0 - x, y0 - y, color_border, size_border);
		put_pixel(x0 - y, y0 - x, color_border, size_border);
		put_pixel(x0 + y, y0 - x, color_border, size_border);
		put_pixel(x0 + x, y0 - y, color_border, size_border);

		if (err <= 0)
		{
			y += 1;
			err += 2*y + 1;
		}else if (err > 0){
			x -= 1;
			err -= 2*x + 1;
		}
	}
}
void circle::view (){
	int radio = sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) ); //Debe ser int ya que la coordenada y da problemas cuando es flotante

	x1_bounding = x1 - radio;
	y1_bounding = y1 - radio;
	x2_bounding = x1 + radio;
	y2_bounding = y1 + radio;

	drawcircle(x1,y1, radio);
	if(selected)
		view_bounding();
};
bool circle::selection(double x, double y){
	if(inside_box(x1_bounding-interval_bounding_box, y1_bounding-interval_bounding_box, x2_bounding+interval_bounding_box,y2_bounding+interval_bounding_box, x,y) )
		return true;

	selected = false;
	return false;
}
void circle::view_bounding(){
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