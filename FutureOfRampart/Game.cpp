#include <iostream>
#include <GL/glut.h>
#include "window.h"
#include "SGGroup.h"
#include "MatrixTransform.h"
#include "Geode.h"
#include "IsoCamera.h"

using namespace std;

#pragma region GAME_GLOBALS
int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
#pragma endregion

#pragma region GAME_HANDLE_INPUT

/**
 * Some keyboard routines to handle turning the spot and point lights
 * on and off.
 */
void handleInput(unsigned char key, int, int)
{
  //IsoCamera.handleInput(key);
}

#pragma endregion

#pragma region GAME_PERSPECTIVE

//----------------------------------------------------------------------------
// Callback method called when window is resized.
void Window::reshapeCallback(int w, int h)
{
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  setPerspective();
}

/**
 * Set our isometric camera perspective.
 */
void Window::setPerspective()
{
  gluPerspective(60,1,1,100);
  gluLookAt(-10, 20, 0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

#pragma endregion

#pragma region GAME_UPDATE

// redraw when we're idle
void Window::idleCallback()
{
  // UPDATE - HANDLE GAME LOGIC HERE BEFORE CALLING DRAW AGAIN

  Window::displayCallback();
}

#pragma endregion

#pragma region GAME_DRAW

void Window::displayCallback()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // initialize the model view matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // DRAW EVERYTHING
  glColor3f(0.0,1.0,0.0);
  glScalef(10.0, 1.0, 10.0);
  glutWireCube(1.0);

  glutSwapBuffers();
}

#pragma endregion

#pragma region OpenGL_Initialization

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);      	      	  // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(Window::width, Window::height);      // set initial window size
  glutCreateWindow("Future of Rampart");  // open window and set window title

  glEnable(GL_DEPTH_TEST);                // enable depth buffering
  glClearColor(0.0, 0.0, 0.0, 1.0);   	  // set clear color to black
  
  // Install callback functions:
  glutDisplayFunc(Window::displayCallback);
  glutIdleFunc(Window::idleCallback);
  glutReshapeFunc(Window::reshapeCallback);

  /* Set the keyboard event handler */
  glutKeyboardFunc(handleInput);

  glutMainLoop();
  return 0;
}

#pragma endregion
