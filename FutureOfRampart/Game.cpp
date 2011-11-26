#include <iostream>
#include <GL/glut.h>
#include "window.h"
#include "SGGroup.h"
#include "MatrixTransform.h"
#include "Geode.h"
#include "IsoCamera.h"
#include "Map.h"

using namespace std;

#pragma region GAME_GLOBALS
int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
Matrix4 worldMatrix; // The world matrix
IsoCamera camera(worldMatrix); // The world camera
SGGroup world;
Map gameMap;
#pragma endregion

#pragma region GAME_HANDLE_INPUT

/**
 * Some keyboard routines to handle turning the spot and point lights
 * on and off.
 */
void handleInput(unsigned char key, int, int)
{
  camera.handleInput(key, 0, 0);
  //Player1.handleInput(key);
  //Player2.handleInput(key);
}

#pragma endregion

#pragma region GAME_INIT

/* initialize the scene graph for the game */
void initializeMap()
{
  world.addChild(&gameMap);
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
  gluPerspective(45,1,1,200);
  gluLookAt(-20, 30, 0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMultMatrixf(worldMatrix.getPointer());
  worldMatrix.print();

  // game scene graph
  glScalef(10.0, 1.0, 10.0);
  glColor3f(0.0,1.0,0.0);
  glutSolidCube(1.0);
  //world.draw(worldMatrix);

  cin.get();
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

  /* initialize the game map */
  initializeMap();

  glutMainLoop();
  return 0;
}

#pragma endregion
