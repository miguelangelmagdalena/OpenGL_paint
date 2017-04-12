#include "figure.h"
#include "triangle.h"

triangle::triangle(float red, float green, float blue, GLfloat size, bool fill, GLfloat size_background, float red2, float green2, float blue2, int widht, int height){
	option = 5;
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
triangle::triangle(float red, float green, float blue, GLfloat size, bool fill, GLfloat size_background, float red2, float green2, float blue2, int widht, int height, 
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
void mediciones_y(double x1, double y1, double x2, double y2, double x3, double y3, double &min_x, double &min_y, double &men_x, double &men_y, double &max_x, double &max_y){
	if(y1 <= y2 && y1 <= y3){
		min_x = x1;
		min_y = y1;
		if(y2>=y3){
			men_x = x3;
			men_y = y3;
			max_x = x2;
			max_y = y2;
		}else{
			men_x = x2;
			men_y = y2;
			max_x = x3;
			max_y = y3;
		}

	}else if(y2 <= y1 && y2 <= y3){
		min_x = x2;
		min_y = y2;
		if(y1>=y3){
			men_x = x3;
			men_y = y3;
			max_x = x1;
			max_y = y1;
		}else{
			men_x = x1;
			men_y = y1;
			max_x = x3;
			max_y = y3;
		}

	}else{
		min_x = x3;
		min_y = y3;

		if(y2>=y1){
			men_x = x1;
			men_y = y1;
			max_x = x2;
			max_y = y2;
		}else{
			men_x = x2;
			men_y = y2;
			max_x = x1;
			max_y = y1;
		}
	}
}

void triangle::view (){
	bresenham(x1,y1,x2,y2);
	bresenham(x1,y1,x3,y3);
	bresenham(x3,y3,x2,y2);
	if(fill_up){
		double min_x, men_x, max_x,min_y, men_y, max_y; 	
		mediciones_y(x1,y1,x2,y2,x3,y3,min_x, min_y, men_x, men_y, max_x, max_y);
		
		/* ¿cOMO LLENAR EL TRIANGULO?
		//double lax = 0, lay = men_y;
		//double aux = -lay + max_y + (lax - max_x)*(max_y-min_y)/(max_x-min_x);
		double lay = men_y;
		double aux = (lay - max_y)* (max_x-min_x)/(max_y-min_y) + max_x;
		//double aux2 = (0- max_x)*(max_y-min_y)/(max_x-min_x)/  + max_y;
		printf("min: %3.2f %3.2f med: %3.2f %3.2f max: %3.2f %3.2f aux: %3.2f\n",min_x, min_y, men_x, men_y, max_x, max_y, aux);

		//if(aux <=0) aux * -1;
		bresenham(aux,men_y,men_x,men_y);
		*/
	}

	mayor_menor(); //Actualiza coordenadas de bounding box
	if(selected)
		view_bounding();
};

double mayor(double x, double y){
	if(x > y)
		return x;
	return y;
}
double menor(double x, double y){
	if(x < y)
		return x;
	return y;
}
void triangle::mayor_menor(){
	x1_bounding = menor(x1,menor(x2,x3));
	y1_bounding = menor(y1,menor(y2,y3));
	x2_bounding = mayor(x1,mayor(x2,x3));
	y2_bounding = mayor(y1,mayor(y2,y3));
}
bool triangle::selection(double x, double y){
	int interval = size_border;
	//mayor_menor();

	if(inside_box(x1_bounding-interval_bounding_box , y1_bounding-interval_bounding_box, x2_bounding+interval_bounding_box,y2_bounding+interval_bounding_box, x,y))
		return true;
	selected = false;
	return false;
}


void triangle::view_bounding(){
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