#ifndef figure_H
#define figure_H
#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <math.h>
#include <AntTweakBar.h>
//#define SCREEN_WIDTH 800
//#define SCREEN_HEIGHT 600

class figure{
	protected:
		double	x1, x2, y1,y2, x3,y3, interval_bounding_box,
				x1_bounding, x2_bounding, y1_bounding, y2_bounding;
		int SCREEN_WIDTH;
		int SCREEN_HEIGHT;
		int option;
		bool selected;
	public:
		typedef struct tipo_color { float color[3]; };
		struct tipo_color color_border, color_background, color_bounding;
		bool fill_up;
		GLfloat size_border, size_background;

		virtual void view() = 0;
		virtual bool selection(double x, double y) = 0;
		virtual void view_bounding() = 0;
		void reshape(int width, int height);
		void put_pixel(double x, double y, struct tipo_color color_border, GLfloat size_border);
		void set_coordinate(double x1, double y1, double x2 , double y2);
		void set_coordinate2(double x2, double y2);
		void set_coordinate3(double x3, double y3);
		void bresenham(double x0, double y0, double x1, double y1);
		void horizontal_line(double x0, double y0, double x1);
		bool inside_box(double x1, double y1, double x2, double y2, double x_element, double y_element);
		void set_selected(bool selection);
	
		double get_x1();
		double get_x2();
		double get_x3();
		double get_y1();
		double get_y2();
		double get_y3();
		
		double get_interval_bounding_box();
		double get_x1_bounding();
		double get_x2_bounding();
		double get_y1_bounding();
		double get_y2_bounding();
		int get_SCREEN_WIDTH();
		int get_SCREEN_HEIGHT();
		int get_option();
		bool get_selected();

		void double_linea_horizontal2(double x0, double y0, double x1, double y1, double y2, struct tipo_color color, struct tipo_color color2, GLfloat size);
		void double_linea_vertical2(double x0, double y0, double x1, double y1, double x2, struct tipo_color color, struct tipo_color color2, GLfloat size);
		
		void set_color(float r, float g, float b);
		float* get_color();
		/*static void TW_CALL set_color_callback(const void *value, void *clientData);
		static void TW_CALL get_color_callback(void *value, void *clientData);*/
};

#endif