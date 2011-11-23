#include <iostream>
#include <GL/glut.h>
#include "window.h"

using namespace std;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

/**
 * Some keyboard routines to handle turning the spot and point lights
 * on and off.
 */
void handleInput(unsigned char key, int, int)
{

}

//----------------------------------------------------------------------------
// Callback method called when window is resized.
void Window::reshapeCallback(int w, int h)
{
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

// redraw when we're idle
void Window::idleCallback()
{
  Window::displayCallback();
}

void Window::displayCallback()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // DRAW EVERYTHING


  glutSwapBuffers();
}

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