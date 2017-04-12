
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include "figure.h"
#include "line.h"
#include "circle.h"
#include "rectangle.h"
#include "ellipse.h"
#include "triangle.h"
int SCREEN_WIDTH =800;
int SCREEN_HEIGHT =600;

#define SELECTION	0
#define LINE		1
#define CIRCLE		2
#define RECTANGLE	3
#define ELLIPSE     4
#define TRIANGLE    5
using namespace std;

double x_pos = 0, y_pos = 0, x2_pos, y2_pos; //For mouse position
int		mouse_option = 0;
int		option = LINE;	 //For figure option
int		cont = 0;
bool	figure_found = false, figure_selected = false, change_size = false;
int		last_selection = -1;
int		cont_move = -1;
char *  nombre = strdup("archivo");

enum figure_type {SELECCION, LINEA, CIRCULO, RECTANGULO, ELIPSE, TRIANGULO};
figure_type figure_option = LINEA;

struct coordenadas{
	double	x1, x2, y1,y2, x3,y3;
};
struct do_stack{
	vector<coordenadas> coordenadas;
	vector<figure*>		figures;
};
vector<figure*> figures;
do_stack figures_undo, figures_redo, aux_figure;
figure * figure_actual= NULL;



void myprogram				(GLFWwindow* window, TwBar *bar);
void error_callback			(int error, const char* description);  
void key_callback			(GLFWwindow* window, int key, int scancode, int action, int mods); 
void mouse_button_callback	(GLFWwindow* window, int button, int action, int mods);
void character_callback		(GLFWwindow* window, unsigned int codepoint);
void on_cursor_pos_callback	(GLFWwindow* window, double mouseX, double mouseY);
void scroll_callback		(GLFWwindow* window, double xoffset, double yoffset);
void reshape				(GLFWwindow* window, int width, int height );
void display();
void TW_CALL set_background_color_callback	(const void *value, void *clientData);
void TW_CALL get_background_color_callback	(void *value, void *clientData);
void TW_CALL set_border_color_callback		(const void *value, void *clientData);
void TW_CALL get_border_color_callback		(void *value, void *clientData);
void TW_CALL set_size_border_callback		(const void *value, void *clientData);
void TW_CALL get_size_border_callback		(void *value, void *clientData);
void TW_CALL set_fill_up_callback			(const void *value, void *clientData);
void TW_CALL get_fill_up_callback			(void *value, void *clientData);
void TW_CALL CopyCDStringToClient(char **destPtr, const char *src);
void save_document();
void line_of_document(string linea);
void charge_document();


int main( void )  
{  
    GLFWwindow* window; //Declare a window object  
    TwBar *bar;         // Pointer to a tweak bar

    glfwSetErrorCallback(error_callback);  //Set the error callback  
  
    //Initialize GLFW  
    if (!glfwInit())  
    {  
		fprintf(stderr, "GLFW failed to initialise");
		exit(EXIT_FAILURE);  
    }  
   
    //Create a window and create its OpenGL context  
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Paint", NULL, NULL);   
    if (!window)  
    {  
        fprintf( stderr, "Failed to open GLFW window.\n" );  
        glfwTerminate();  
        exit(EXIT_FAILURE);  
    }  

	// Initialize AntTweakBar
    TwInit(TW_OPENGL, NULL);
	bar = TwNewBar("Ayuda");
    TwDefine(" GLOBAL help='Paint OpenGL + AntTeawkBar' "); // Message added to the help bar.
	TwWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	TwCopyCDStringToClientFunc(CopyCDStringToClient);

	//MOUSE EVENTS:
	glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetMouseButtonCallback( window, mouse_button_callback);
	glfwSetInputMode (window, GLFW_STICKY_MOUSE_BUTTONS, 1);
	
	//Other events:
    glfwSetKeyCallback(window, key_callback);  //Sets the key callback for exit   
	glfwSetFramebufferSizeCallback(window, reshape);
	glfwSetCharCallback(window,character_callback);
	glfwSetCursorPosCallback(window, on_cursor_pos_callback);
	glfwSetScrollCallback(window, scroll_callback);

    //This function makes the context of the specified window current on the calling thread.   
    glfwMakeContextCurrent(window);  
  
	//Other general options
	display();
	
	// Create a new TwType called rotationType associated with the Scene::RotMode enum, and use it
	TwEnumVal figures_types[] = {	{ SELECCION,	"Seleccion"}, 
									{ LINEA,		"Linea" }, 
									{ CIRCULO,		"Circulo" },
									{ RECTANGULO,	"Rectangulo" }, 
									{ ELIPSE,		"Elipse" }, 
									{ TRIANGULO,	"Triangulo" }};
    TwType rotationType = TwDefineEnum( "Modo", figures_types, 6 );
    TwAddVarRW(bar, "Modo", rotationType, &figure_option, " help='Elegir modo a trabajar' ");
	TwAddVarCB(bar, "Relleno", TW_TYPE_BOOLCPP, set_fill_up_callback,get_fill_up_callback,&figure_actual->fill_up, "");
	TwAddVarCB(bar, "Tam Borde",	TW_TYPE_FLOAT, set_size_border_callback, get_size_border_callback,&figure_actual->size_border, " min=2 max=16 step=2 ");
	TwAddVarCB(bar, "Fondo", TW_TYPE_COLOR3F, set_background_color_callback, get_background_color_callback, &figure_actual->color_background, "group='Color'");
    TwAddVarCB(bar, "Borde", TW_TYPE_COLOR3F, set_border_color_callback, get_border_color_callback, &figure_actual->color_background, "group='Color'");
	TwAddVarRW(bar, "Nombre Archivo", TW_TYPE_CDSTRING, &nombre, "group='Guardar/Cargar Archivo'");
	
	//****Main Loop****
    do{  
        //Clear color buffer  
        glClear(GL_COLOR_BUFFER_BIT);  
  
		//### FOR RENDERING OpengGl HERE ###
		glfwGetCursorPos(window, &x_pos, & y_pos);
		myprogram(window, bar);
		//### FOR RENDERING OpengGl HERE ###

		//Draw tweak bars
        TwDraw();
        //Swap buffers  its like glfwflush xD
        glfwSwapBuffers(window);  
        //Get and organize events, like keyboard and mouse input, window resizing, etc...  
        glfwPollEvents();  
		
    } //Check if the ESC key had been pressed or if the window had been closed  
    while (!glfwWindowShouldClose(window));  
  
    //Close OpenGL window and terminate GLFW  
    glfwDestroyWindow(window);  
    //Finalize and clean up GLFW 
	TwTerminate();
    glfwTerminate();  
  
    exit(EXIT_SUCCESS);  
}  
//Define an error callback  
void error_callback(int error, const char* description)  
{  
    fputs(description, stderr);  
    _fgetchar();  
}
//Define the key input callback  
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)  
{  
    if( !TwEventKeyGLFW(key, action) )  // Send event to AntTweakBar
    {
		// Event has not been handled by AntTweakBar
        // Do something if needed.
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)  
			glfwSetWindowShouldClose(window, GL_TRUE);  
	
		if(key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS && last_selection != -1 && figure_selected == true){//Delete selected figures			
			figures[last_selection]->set_selected(false);

			figures_undo.figures.push_back(figures[last_selection]);
			figures.erase(figures.begin()+ last_selection);

			last_selection =-1;
			figure_selected = false;
		} else if(key == GLFW_KEY_Z && action == GLFW_PRESS ){ //Undo

			if(!figures_undo.figures.empty()){
				figures.push_back(figures_undo.figures.back());
				figures_redo.figures.push_back(figures_undo.figures.back());
				figures_undo.figures.pop_back();

			}else if(!figures.empty()){
				if(last_selection != -1 && figure_selected == true){
					if(figures.back() == figures[last_selection]){
						figures[last_selection]->set_selected(false);
						last_selection =-1;
						figure_selected = false;
					}
				}

				figures_redo.figures.push_back(figures.back());
				figures.pop_back();
			}
		} else if(key == GLFW_KEY_Y && action == GLFW_PRESS){//Redo
			if(!figures_redo.figures.empty()){
				figures.push_back(figures_redo.figures.back());
				figures_redo.figures.pop_back();
			}

		}else if(key == GLFW_KEY_F1 && action == GLFW_PRESS){//Save
			save_document();
		}else if(key == GLFW_KEY_F2 && action == GLFW_PRESS){//Charge
			charge_document();
		}

	}
}
//Define when mouse button is press
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
	if( !TwEventMouseButtonGLFW(button, action) )   // Send event to AntTweakBar
    {
        // Event has not been handled by AntTweakBar
        // Do something if needed.
		if( button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
			mouse_option = 1;
		}else if( button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
			mouse_option = 0;
			if(cont_move ==1 ){
				//printf("no \n");

				//figures_undo.figures.push_back.push_back(aux_figure);
				
			}
			cont_move = -1;
		}
    }
	
	
}
void character_callback(GLFWwindow* window, unsigned int codepoint)
{
	if( !TwEventCharGLFW(codepoint, GLFW_PRESS) )    // Send event to AntTweakBar
    {
        // Event has not been handled by AntTweakBar
        // Do something if needed.
    }
}
void on_cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY)
{
    if( !TwEventMousePosGLFW(mouseX, mouseY) )  // Send event to AntTweakBar
    {
        // Event has not been handled by AntTweakBar
        // Do something if needed.
    }
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if( !TwEventMouseWheelGLFW(yoffset) )   // Send event to AntTweakBar
    {
        // Event has not been handled by AntTweakBar
        // Do something if needed.
    }
}
//Other general options
void display(){

	glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT ); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode( GL_PROJECTION );	// projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity( ); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    glOrtho( 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1 ); // essentially set coordinate system
    glMatrixMode( GL_MODELVIEW ); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity( ); // same as above comment
	
    //Set a background color  
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
}
// Callback function called by GLFW when window size changes
void reshape( GLFWwindow* window, int width, int height )
{
	
	//#undef SCREEN_WIDTH
	SCREEN_WIDTH =width;
	SCREEN_HEIGHT =height;
	display();

	 // Send the new window size to AntTweakBar
    TwWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	change_size = true;
}
void myprogram(GLFWwindow* window, TwBar *bar){
	figure* actual;
	float red, green, blue; GLfloat size; bool fill; GLfloat size_background; float red2, green2, blue2;
	red = 0.0; green = 0.0; blue = 0.0; size = 2;
	fill = true; size_background = size; 
	red2	= 0.0;green2	= 0.0; blue2	= 1.0;
	
	if(figure_option == SELECCION)
			option = SELECTION;
	else if(figure_option == LINEA)
		option = LINE;
	else if(figure_option == CIRCULO)
		option = CIRCLE;
	else if(figure_option == RECTANGULO)
		option = RECTANGLE;
	else if(figure_option == ELIPSE)
		option = ELLIPSE;
	else if(figure_option == TRIANGULO)
		option = TRIANGLE;

	switch (option){
		case LINE:
			actual = new line		(red, green, blue, size, fill, size_background, red2, green2, blue2, SCREEN_WIDTH, SCREEN_HEIGHT);
		break;
		case CIRCLE:
			actual = new circle		(red, green, blue, size, fill, size_background, red2, green2, blue2, SCREEN_WIDTH, SCREEN_HEIGHT);
		break;
		case ELLIPSE:
			actual = new ellipse	(red, green, blue, size, fill, size_background, red2, green2, blue2, SCREEN_WIDTH, SCREEN_HEIGHT);
		break;
		case RECTANGLE:
			actual = new rectangle	(red, green, blue, size, fill, size_background, red2, green2, blue2, SCREEN_WIDTH, SCREEN_HEIGHT);
		break;
		case TRIANGLE:
			actual = new triangle	(red, green, blue, size, fill, size_background, red2, green2, blue2, SCREEN_WIDTH, SCREEN_HEIGHT);
		break;
	}
	
	if(option == SELECTION){
		if(mouse_option == 1){
			
			//Iterator in reverse for stack simulation
			for(int i = figures.size() -1;   i >=0 && figure_found != true; --i) {
				if(figures[i]->selection(x_pos,y_pos)){
					
					figure_found = true;
					

					if(last_selection !=-1 && last_selection != i){
						figures[last_selection]->set_selected(false); //Quitamos la ultima seleccionada
						figure_selected = false;
						figure_actual = NULL;
						//cont_move = -1;
					}

					figures[i]->set_selected(true);
					figures[i]->view_bounding();
					last_selection = i;
					figure_actual = figures[last_selection];
					figure_selected = true;
					mouse_option = 2;

					//Last mouse position
					x2_pos = x_pos; y2_pos = y_pos;

					if(cont_move == -1){
						
						coordenadas aux;
						aux.x1 = figures[last_selection]->get_x1();
						aux.x2 = figures[last_selection]->get_x2();
						aux.x3 = figures[last_selection]->get_x3();
						aux.y1 = figures[last_selection]->get_y1();
						aux.y2 = figures[last_selection]->get_y2();
						aux.y3 = figures[last_selection]->get_y3();
						//printf("original %f.3 %f.3 %f.3 %f.3 %f.3 ",aux.x1,aux.x2,aux.x3,aux.y1,aux.y2,aux.y3);
						aux_figure.coordenadas.push_back(aux);

						cont_move=0;
					}
					/*}else if (aux_figure != figures[last_selection] ){ // nueva fig
						
						
						aux_figure = figures[last_selection];
						cont_move=0;
					}*/
				}
			}
		}else if(mouse_option == 2){//Button in moving

			if(figure_found = true){
				double x1 = figures[last_selection]->get_x1(),
					   y1 = figures[last_selection]->get_y1(),
					   x2 = figures[last_selection]->get_x2(),
					   y2 = figures[last_selection]->get_y2(),
					   x3 = figures[last_selection]->get_x3(),
					   y3 = figures[last_selection]->get_y3();
				double moving_x = 0, moving_y = 0;
				double aux;

				/*if(cont_move == -1){
					figures_undo.push_back(figures[last_selection]);
					figures_undo_moves.push_back(last_selection);
				}*/

				aux =  (x_pos - x2_pos );
				if(aux> 0 )//Move up
					moving_x = (aux);
				aux=(x_pos - x2_pos);
				if(aux< 0 )//Move down
					moving_x = (aux);
				aux=(y_pos - y2_pos);
				if(aux >0)//Move right
					moving_y = (aux);
				aux=(y_pos - y2_pos);
				if(aux <0)//Move left
					moving_y = (aux);

				figures[last_selection]->set_coordinate(x1+moving_x,y1+moving_y,x2+moving_x, y2+moving_y);
				figures[last_selection]->set_coordinate3(x3 + moving_x, y3 + moving_y);	//if(option == TRIANGLE)

				if((x2_pos != x_pos || y2_pos != y_pos) ){
					//Last mouse position
					x2_pos = x_pos; y2_pos = y_pos;
					if(cont_move ==0){
						cont_move = 1;
					}

					//cont_move = 1;
				}else{
					/*if(cont_move ==0){
						cont_move = -1;
					}*/
					//cont_move = -1;
					/*if(!figures_undo.empty() && cont_move != -1){
						figures_undo.pop_back();
						figures_undo_moves.pop_back();
					}*/
					//figures_undo_moves.pop_back();

				}
			}
		}
		
		
	}else{

		if(figure_selected && last_selection !=-1){
			figures[last_selection]->set_selected(false); //Quitamos la ultima seleccionada
			figure_selected = false;
			figure_actual = NULL;
		}

		//Handling events for mouse:
		if(option == TRIANGLE && cont ==2 ){
			figures.back()->set_coordinate3(x_pos, y_pos);
			if(mouse_option == 1){
				cont = 0;
				mouse_option = 0;
			}	
		}

		if(mouse_option == 1){//During button pressed
			actual ->set_coordinate(x_pos,y_pos,x_pos,y_pos);

			if(!figures_redo.figures.empty()){ //We clear the redo stack
				figures_redo.figures.clear();
			}

			figures.push_back(&(*actual));
			mouse_option = 2;
			cont = 1;
		}else if(mouse_option == 2){//Button in moving
			figures.back()->set_coordinate2(x_pos, y_pos);
			cont = 2;
		}
	}
	
	if(figure_found==true){
		figure_found = false;
	}

	//Imprimimos las figuras
	if(!figures.empty()){
		
		for(vector<figure>::size_type i = 0; i != figures.size(); i++) {
			//actual = lineas[i];
			figures[i]->view();
			if(change_size)figures[i]->reshape(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
	}
}
void TW_CALL set_background_color_callback	(const void *value, void *clientData){
	(void)clientData; // unused
	float  *new_color = (float *)value;

	//printf("color: %f colo2r: %f \n" , new_color[0], new_color[1]);
	if(figure_actual != NULL && figure_selected && figure_actual->get_selected()){
		figure_actual->color_background.color[0] = new_color[0];
		figure_actual->color_background.color[1] = new_color[1];
		figure_actual->color_background.color[2] = new_color[2];
	}
}
void TW_CALL get_background_color_callback	(void *value, void *clientData){
	(void)clientData; // unused

	float  color[3];
	if(figure_actual != NULL && figure_selected && figure_actual->get_selected()){
		color[0] = figure_actual->color_background.color[0];
		color[1] = figure_actual->color_background.color[1];
		color[2] = figure_actual->color_background.color[2];
		//printf("color: %f colo2r: %f colo3r: %f \n" , color[0], color[1],color[2]);
		*(float **)(value) = color;
	}else
		*static_cast<float **>(value) = figure_actual->color_background.color; 
}
void TW_CALL set_border_color_callback		(const void *value, void *clientData){
	(void)clientData; // unused
	float  *new_color = (float *)value;

	//printf("color: %f colo2r: %f \n" , new_color[0], new_color[1]);
	if(figure_actual != NULL && figure_selected && figure_actual->get_selected()){
		figure_actual->color_border.color[0] = new_color[0];
		figure_actual->color_border.color[1] = new_color[1];
		figure_actual->color_border.color[2] = new_color[2];
	}
}
void TW_CALL get_border_color_callback		(void *value, void *clientData){
	(void)clientData; // unused

	float  color[3];
	if(figure_actual != NULL && figure_selected && figure_actual->get_selected()){
		color[0] = figure_actual->color_border.color[0];
		color[1] = figure_actual->color_border.color[1];
		color[2] = figure_actual->color_border.color[2];
		//printf("color: %f colo2r: %f colo3r: %f \n" , color[0], color[1],color[2]);
		*(float **)(value) = color;
	}else
		*static_cast<float **>(value) = figure_actual->color_border.color; 
}
void TW_CALL set_size_border_callback		(const void *value, void *clientData){
	(void)clientData; // unused
	GLfloat size_border = *(const GLfloat*)value;
	if(figure_actual != NULL && figure_selected && figure_actual->get_selected()){
		figure_actual->size_border = size_border;
	}
}
void TW_CALL get_size_border_callback		(void *value, void *clientData){
	(void)clientData; // unused
	if(figure_actual != NULL && figure_selected && figure_actual->get_selected()){
		*(float *)(value) = figure_actual->size_border;
	}else
	*static_cast<float *>(value) = 2;
}
void TW_CALL set_fill_up_callback			(const void *value, void *clientData){
	(void)clientData; // unused
	bool fill = *(const bool*)value;
	if(figure_actual != NULL && figure_selected && figure_actual->get_selected()){
		figure_actual->fill_up = fill;
	}
}
void TW_CALL get_fill_up_callback			(void *value, void *clientData){
	(void)clientData; // unused
	if(figure_actual != NULL && figure_selected && figure_actual->get_selected()){
		*(bool *)(value) = figure_actual->fill_up;
	}
	//*static_cast<float *>(value) = 2;
}
// Function called by AntTweakBar to copy the content of a C-Dynamic String (src) handled
// by the AntTweakBar library to a C-Dynamic string (*destPtr) handled by your application
void TW_CALL CopyCDStringToClient(char **destPtr, const char *src)
{
  size_t srcLen = (src!=NULL) ? strlen(src) : 0;
  size_t destLen = (*destPtr!=NULL) ? strlen(*destPtr) : 0;
 
  // alloc or realloc dest memory block if needed
  if( *destPtr==NULL )
    *destPtr = (char *)malloc(srcLen+1);
  else if( srcLen>destLen )
    *destPtr = (char *)realloc(*destPtr, srcLen+1);
 
  // copy src
  if( srcLen>0 )
    strncpy(*destPtr, src, srcLen);
  (*destPtr)[srcLen] = '\0'; // null-terminated string
}
void save_document(){
	ofstream myfile;
	char cadena[200];
	strcpy(cadena,"files/");
	strcat(cadena,nombre);
	strcat(cadena,".MM_PAIN");
	myfile.open (cadena);
	if (myfile.is_open())
	{

		//Iterator in reverse for stack simulation
		for(int i = figures.size() -1;   i >=0 && figure_found != true; --i) {
			myfile<<figures[i]->get_option()<<" ";
			myfile<<figures[i]->get_x1()<<" ";
			myfile<<figures[i]->get_x2()<<" ";
			myfile<<figures[i]->get_x3()<<" ";
			myfile<<figures[i]->get_y1()<<" ";
			myfile<<figures[i]->get_y2()<<" ";
			myfile<<figures[i]->get_y3()<<" ";
			myfile<<figures[i]->get_SCREEN_WIDTH()<<" ";
			myfile<<figures[i]->get_SCREEN_HEIGHT()<<" ";
			myfile<<figures[i]->color_border.color[0]<<" ";
			myfile<<figures[i]->color_border.color[1]<<" ";
			myfile<<figures[i]->color_border.color[2]<<" ";
			myfile<<figures[i]->color_background.color[0]<<" ";
			myfile<<figures[i]->color_background.color[1]<<" ";
			myfile<<figures[i]->color_background.color[2]<<" ";
			myfile<<figures[i]->fill_up<<" ";
			myfile<<figures[i]->size_border<<" ";
			myfile<<figures[i]->size_background<<" ";
			myfile<<"\n";

		}

		myfile.close();
	}else{
		printf("Error, no se pudo abrir el archivo para guardar\n");
	}
}
void line_of_document(string linea){
	figure* actual;
	float red, green, blue; GLfloat size; bool fill; GLfloat size_background; float red2, green2, blue2;
	int cont = 0;

	double	x1, x2, y1,y2, x3,y3;
	int SCREEN_WIDTH, SCREEN_HEIGHT;

	int j = 0;
	char aux[100];

	for(int i=0; i<= linea.length(); i++,j++){
		
		if(linea[i]== ' ' || linea[i]== '\0'){
			

			aux[j] = '\0';
			//printf("%s. ",aux);
			j=0;
			cont++;

			if(cont==1){
				option = atoi(aux);
			}else if(cont==2){
				x1	= atof(aux);	
			}else if(cont==3){
				x2	= atof(aux);
			}else if(cont==4){
				x3	= atof(aux);
			}else if(cont==5){
				y1	= atof(aux);
			}else if(cont==6){
				y2	= atof(aux);
			}else if(cont==7){
				y3	= atof(aux);
			}else if(cont==8){
				SCREEN_WIDTH = atoi(aux);
			}else if(cont==9){
				SCREEN_HEIGHT = atoi(aux);
			}else if(cont==10){
				red = atof(aux);
			}else if(cont==11){
				green = atof(aux);
			}else if(cont==12){
				blue = atof(aux);
			}else if(cont==13){
				red2 = atof(aux);
			}else if(cont==14){
				green2 = atof(aux);
			}else if(cont==15){
				blue2 = atof(aux);
			}else if(cont==16){
				fill = atoi(aux);
			}else if(cont==17){
				size = atof(aux);
			}else if(cont==18){
				size_background = atof(aux);
				
				printf("\n\n");
				size_background = size;
				
				switch (option){
					case LINE:
						actual = new line		(red, green, blue, size, fill, size_background, red2, green2, blue2, SCREEN_WIDTH, SCREEN_HEIGHT, x1, x2, y1,y2, x3,y3);
					break;
					case CIRCLE:
						actual = new circle		(red, green, blue, size, fill, size_background, red2, green2, blue2, SCREEN_WIDTH, SCREEN_HEIGHT, x1, x2, y1,y2, x3,y3);
					break;
					case ELLIPSE:
						actual = new ellipse	(red, green, blue, size, fill, size_background, red2, green2, blue2, SCREEN_WIDTH, SCREEN_HEIGHT, x1, x2, y1,y2, x3,y3);
					break;
					case RECTANGLE:
						actual = new rectangle	(red, green, blue, size, fill, size_background, red2, green2, blue2, SCREEN_WIDTH, SCREEN_HEIGHT, x1, x2, y1,y2, x3,y3);
					break;
					case TRIANGLE:
						actual = new triangle	(red, green, blue, size, fill, size_background, red2, green2, blue2, SCREEN_WIDTH, SCREEN_HEIGHT, x1, x2, y1,y2, x3,y3);
					break;
				}
				figures.push_back(actual);
			}
		}
		aux[j] = linea[i];

	}
}
void charge_document(){

	string line;
	char cadena[200];
	strcpy(cadena,"files/");
	strcat(cadena,nombre);
	strcat(cadena,".MM_PAIN");

	ifstream myfile (cadena);
	if (myfile.is_open()) {
		//Inicializamos la aplicación de nuevo
		figures.clear();
		figures_undo.coordenadas.clear();
		figures_undo.figures.clear();
		figures_redo.coordenadas.clear();
		figures_redo.figures.clear();

		while ( getline (myfile,line) )    {
			line_of_document(line);
			//cout << line << '\n\n';

		}
		myfile.close();
	}else{
		printf("Error, no se pudo abrir el archivo\n");
	}
}

