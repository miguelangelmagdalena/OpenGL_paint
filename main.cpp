#include <GL/glew.h>  
#include <GLFW/glfw3.h>   
#include <stdio.h>  
#include <stdlib.h> 
#include <iostream>

#define SCREEN_WIDHT 640
#define SCREEN_HEIGHT 480

//Define an error callback  
static void error_callback(int error, const char* description);  
//Define the key input callback  
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods); 
  
//Define cursor moving callback
static void cursor_position_callback(GLFWwindow* window, double x_pos, double y_pos);
//Define if cursor is inside window
void cursor_enter_callback(GLFWwindow* window, int entered);
//Define when mouse button is press
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

//
void myprogram(){
	
}

int main( void )  
{  
    //Set the error callback  
    glfwSetErrorCallback(error_callback);  
  
    //Initialize GLFW  
    if (!glfwInit())  
    {  
		fprintf(stderr, "GLFW failed to initialise");
		exit(EXIT_FAILURE);  
    }  
  
    //*Set the GLFW window creation hints - these are optional*  
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version  
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version  
    glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing  
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  
  
    //Declare a window object  
    GLFWwindow* window;  
  
    //Create a window and create its OpenGL context  
	window = glfwCreateWindow(SCREEN_WIDHT, SCREEN_HEIGHT, "Test Window", NULL, NULL);  
  
	//MOUSE EVENTS:
	glfwSetCursorPosCallback( window, cursor_position_callback);
	glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorEnterCallback( window, cursor_enter_callback);
	glfwSetMouseButtonCallback( window, mouse_button_callback);
	glfwSetInputMode (window, GLFW_STICKY_MOUSE_BUTTONS, 1);
	
	//If the window couldn't be created  
    if (!window)  
    {  
        fprintf( stderr, "Failed to open GLFW window.\n" );  
        glfwTerminate();  
        exit(EXIT_FAILURE);  
    }  
  
    //This function makes the context of the specified window current on the calling thread.   
    glfwMakeContextCurrent(window);  
  
    //Sets the key callback  
    glfwSetKeyCallback(window, key_callback);  
  
    //Initialize GLEW  
    GLenum err = glewInit();  
  
    //If GLEW hasn't initialized  
    if (err != GLEW_OK)   
    {  
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));  
        return -1;  
    }  
  
    //Set a background color  
    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);  
  
    //****Main Loop****
    do  
    {  
        //Clear color buffer  
        glClear(GL_COLOR_BUFFER_BIT);  
  
		/***FOR RENDERING OpengGl here***/
		myprogram();

		
		/*Pos actual of cursor
		double x_pos, y_pos;
		glfwGetCursorPos(window, &x_pos, & y_pos);
		printf("x: %f \ny: %f \n\n",x_pos, y_pos);
		*/

        //Swap buffers  
        glfwSwapBuffers(window);  
        //Get and organize events, like keyboard and mouse input, window resizing, etc...  
        glfwPollEvents();  
		
    } //Check if the ESC key had been pressed or if the window had been closed  
    while (!glfwWindowShouldClose(window));  
	//****Main Loop****
  
    //Close OpenGL window and terminate GLFW  
    glfwDestroyWindow(window);  
    //Finalize and clean up GLFW  
    glfwTerminate();  
  
    exit(EXIT_SUCCESS);  
}  

//Define an error callback  
static void error_callback(int error, const char* description)  
{  
    fputs(description, stderr);  
    _fgetchar();  
}
//Define the key input callback  
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)  
{  
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)  
    glfwSetWindowShouldClose(window, GL_TRUE);  
}
//Define cursor moving callback
static void cursor_position_callback(GLFWwindow* window, double x_pos, double y_pos)
{
	//printf("x: %f \ny: %f \n\n",x_pos, y_pos);
}
//Define if mouse its inside window
void cursor_enter_callback(GLFWwindow* window, int entered){
	if (entered)	{printf("Dentro de la ventana \n");}
	else			{printf("Fuera de la ventana  \n");}
}
//Define when mouse button is press
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
	double x_pos, y_pos;
	if( button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
		printf("Boton izquierdo presionado \n");
		
		glfwGetCursorPos(window, &x_pos, & y_pos);
		printf("x: %f \ny: %f \n\n",x_pos, y_pos);
	}else if( button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
		printf("Boton izquierdo soltado    \n");

		glfwGetCursorPos(window, &x_pos, & y_pos);
		printf("x: %f \ny: %f \n\n",x_pos, y_pos);
	}
}