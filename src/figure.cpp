#include "figure.h"
void figure::reshape(int width, int height){
	SCREEN_WIDTH	= width;
	SCREEN_HEIGHT	= height;
}
void figure::set_coordinate(double x1, double y1, double x2 , double y2){
	this -> x1 = x1;
	this -> x2 = x2;
	this -> y1 = y1;
	this -> y2 = y2;
	this -> x3 = x1;
	this -> y3 = y1; 
};
void figure::set_coordinate2(double x2, double y2){
	this -> x2 = x2;
	this -> y2 = y2;
};
void figure::set_coordinate3(double x3, double y3){
	this -> x3 = x3;
	this -> y3 = y3;
};
void figure::put_pixel(double x, double y, struct tipo_color color_border, GLfloat size_border){
	double	y2 = SCREEN_HEIGHT - y;
	double	x2 = x;

	glPointSize( size_border );
	glColor3f(color_border.color[0], color_border.color[1], color_border.color[2]);
	glBegin(GL_POINTS);
	glVertex2d(x2,y2);
	glEnd();
};
void figure::bresenham(double x0, double y0, double x1, double y1) { 
	double x, y, dx, dy, p, incE, incNE, stepx, stepy;
	dx = (x1 - x0);
	dy = (y1 - y0);

	// determinar que punto usar para empezar, cual para terminar 
	if (dy < 0) { 
		dy = -dy; 
		stepy = -1; 
	} else {
		stepy = 1;
	}

	if (dx < 0) {  
		dx = -dx;  
		stepx = -1; 
	} else {
		stepx = 1;
	}

	x = x0;
	y = y0;

	put_pixel(x0,y0,color_border,size_border);

	//se cicla hasta llegar al extremo de la línea /
	if(dx>dy){
		p = 2*dy - dx;
		incE = 2*dy;
		incNE = 2*(dy-dx);
		while (x != x1){
			x = x + stepx;
			if (p < 0){
				p = p + incE;
			} else {
				y = y + stepy;
				p = p + incNE;
			}
			put_pixel(x,y,color_border,size_border);
		}
	}else{
		p = 2*dx - dy;
		incE = 2*dx;
		incNE = 2*(dx-dy);
		while (y != y1){
			y = y + stepy;
			if (p < 0){
				p = p + incE;
			} else {
				x = x + stepx;
				p = p + incNE;
			}
			put_pixel(x,y,color_border,size_border);
		}
	}
};
void figure::horizontal_line(double x0, double y0, double x1){
	double  stepx;
	//dy = (y1 - y0);

	// determinar que punto usar para empezar, cual para terminar 

	if ((x1 - x0) < 0) {  
		stepx = -1; 
	} else {
		stepx = 1;
	}


	put_pixel(x1,y1,color_background,size_background);
	while (x0 != x1){
		x0 = x0 + stepx;
		put_pixel(x0,y0,color_background,size_background);
	}

}
bool figure::inside_box(double x1, double y1, double x2, double y2, double x_element, double y_element){
	bool hypothesis = false;
	double aux;
	y1 = SCREEN_HEIGHT - y1;
	y2 = SCREEN_HEIGHT - y2;
	y_element = SCREEN_HEIGHT - y_element;

	if(x1 > x2){ aux=x1; x1=x2; x2=aux;}
	if(y1 > y2){ aux=y1; y1=y2; y2=aux;}

	if( (x_element>= x1 && x_element <= x2)  && (y_element>= y1 && y_element <= y2))
		hypothesis = true;


	return hypothesis;
}
void figure::set_selected(bool selection){
	selected = selection;
}

double figure::get_x1(){
	return x1;
}
double figure::get_x2(){
	return x2;
}
double figure::get_x3(){
	return x3;
}
double figure::get_y1(){
	return y1;
}
double figure::get_y2(){
	return y2;
}
double figure::get_y3(){
	return y3;
}

double figure::get_interval_bounding_box(){
	return interval_bounding_box;
}
double figure::get_x1_bounding(){
	return x1_bounding;
}
double figure::get_x2_bounding(){
	return x2_bounding;
}
double figure::get_y1_bounding(){
	return y1_bounding;
}
double figure::get_y2_bounding(){
	return y2_bounding;
}
int figure::get_SCREEN_WIDTH(){
	return SCREEN_WIDTH;
}
int figure::get_SCREEN_HEIGHT(){
	return SCREEN_HEIGHT;
}
int figure::get_option(){
	return option;
}
bool figure::get_selected(){
	return selected;
}
void figure::double_linea_horizontal2(double x0, double y0, double x1, double y1, double y2, struct tipo_color color, struct tipo_color color2, GLfloat size){
	double stepx;
	int cont = 1;
	// determinar que punto usar para empezar, cual para terminar 
	if ((x1 - x0) < 0) {  
		stepx = -1; 
	} else {
		stepx = 1;
	}

	put_pixel(x1,y1,color,size);
	put_pixel(x1,y2,color,size);
	//se cicla hasta llegar al extremo de la línea /
	
	while (x0 != x1){
		x0 = x0 + stepx;
		
		if( cont>=5){
			put_pixel(x0,y0,color,size);
			put_pixel(x0,y2,color,size);
			if(cont==10)cont = 1;
		}else{
			put_pixel(x0,y0,color2,size);
			put_pixel(x0,y2,color2,size);
		}
		cont++;
	}

};
void figure::double_linea_vertical2(double x0, double y0, double x1, double y1, double x2, struct tipo_color color, struct tipo_color color2, GLfloat size)
{
	double stepy;
	int cont = 1;
	// determinar que punto usar para empezar, cual para terminar 
	if ((y1 - y0) < 0) { 
		stepy = -1; 
	} else {
		stepy = 1;
	}

	put_pixel(x1,y1,color,size);
	put_pixel(x2,y1,color,size);
	//se cicla hasta llegar al extremo de la línea /

	while (y0 != y1){
		y0 = y0 + stepy;

		if( cont>=5){
			put_pixel(x0,y0,color,size);
			put_pixel(x2,y0,color,size);
			if(cont==10)cont = 1;
		}else{
			put_pixel(x0,y0,color2,size);
			put_pixel(x2,y0,color2,size);
		}
		
		cont++;
		
	}
};

void figure::set_color(float r, float g, float b){
	color_background.color[0] =  r;
	color_background.color[1] =  g;
	color_background.color[2] =  b;
}
float* figure::get_color(){
	return color_background.color;
}
/*static void TW_CALL set_color_callback(const void *value, void *clientData){
	static_cast<figure *>(clientData)->set_color(*static_cast<const float *>(value),*static_cast<const float *>(value),*static_cast<const float *>(value));
}
static void TW_CALL get_color_callback(void *value, void *clientData){
	*static_cast<float **>(value) = static_cast<figure *>(clientData)->get_color();
}*/
