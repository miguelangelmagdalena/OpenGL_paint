#include "figure.h"
#include "line.h"

line::line(float red, float green, float blue, GLfloat size, bool fill, GLfloat size_background, float red2, float green2, float blue2, int widht, int height){
	option = 1;
	color_border.color[0]	= red;
	color_border.color[1]	= green;
	color_border.color[2]	= blue;
	size_border				= size;
	fill_up					= fill;
	this->size_background			= size_background;
	color_background.color[0]	= red2;
	color_background.color[1]	= green2;
	color_background.color[2]	= blue2;
	interval_bounding_box	= size_border + 3;
	selected = false;
	SCREEN_WIDTH = widht;
	SCREEN_HEIGHT = height;
};
line::line(float red, float green, float blue, GLfloat size, bool fill, GLfloat size_background, float red2, float green2, float blue2, int widht, int height, 
		   double	x1, double x2, double y1,double y2,double  x3,double y3){
	option = 1;
	color_border.color[0]	= red;
	color_border.color[1]	= green;
	color_border.color[2]	= blue;
	size_border				= size;
	fill_up					= fill;
	this->size_background			= size_background;
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
void line::view () {
	put_pixel(x1,y1,color_border,size_border);
	if(this ->x1 > this ->x2){x1_bounding= this->x2; x2_bounding= this->x1;}else{x1_bounding= this->x1; x2_bounding= this->x2;}
	if(this ->y1 > this ->y2){y1_bounding= this->y2; y2_bounding= this->y1;}else{y1_bounding= this->y1; y2_bounding= this->y2;}

	bresenham(x1,y1,x2,y2);
	if(selected)
		view_bounding();
};
bool line::selection(double x, double y){
	if(inside_box(x1_bounding-interval_bounding_box, y1_bounding-interval_bounding_box, x2_bounding+interval_bounding_box,y2_bounding+interval_bounding_box, x,y) )
		return true;

	selected = false;
	return false;
}
void line::view_bounding(){
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