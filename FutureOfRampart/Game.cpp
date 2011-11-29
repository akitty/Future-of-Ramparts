#include <iostream>
#include <GL/glut.h>
#include "window.h"
#include "SGGroup.h"
#include "MatrixTransform.h"
#include "Geode.h"
#include "IsoCamera.h"
#include "TextureManager.h"
#include "imageloader.h"
#include "TextureNumbers.h"
#include "Map.h"

using namespace std;

#pragma region GAME_GLOBALS
int Window::width  = 1024;   // set window width in pixels here
int Window::height = 768;   // set window height in pixels here
Matrix4 worldMatrix; // The world matrix
IsoCamera camera(worldMatrix); // The world camera
SGGroup world;
Map* gameMap;
Block* testBlock;
Image* textures[NUM_TEXTURES];
GLuint textureNums[NUM_TEXTURES];
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
  gameMap = new Map(textureNums);
  world.addChild(gameMap);
}

/* Load all of the assets associated with this game
   and pass them where they need to go */
void loadAssets()
{
  // load textures
  textures[0] = loadBMP("map_top_base.bmp");
  textures[1] = loadBMP("map_top_p1.bmp");
  textures[2] = loadBMP("map_top_p2.bmp");
  textures[3] = loadBMP("map_front.bmp");
  textures[4] = loadBMP("map_back.bmp");
  textures[5] = loadBMP("map_left.bmp");
  textures[6] = loadBMP("map_right.bmp");
  textures[7] = loadBMP("block_top.bmp");
  textures[8] = loadBMP("block_front.bmp");
  textures[9] = loadBMP("block_back.bmp");
  textures[10] = loadBMP("block_left.bmp");
  textures[11] = loadBMP("block_right.bmp");

  // create space for all of the textures
  glGenTextures(NUM_TEXTURES, textureNums);

  for(int i = 0; i < NUM_TEXTURES; ++i)
  {
    // load each one in
    TextureManager::loadTexture(textures[i], textureNums[i]);
  }
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
  gluLookAt(0, 50, 30, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void initializeCamera()
{
  camera.isometrize();
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

  // game scene graph
  //glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
  world.draw(worldMatrix);

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
  loadAssets();
  initializeMap();
  initializeCamera();

  glutMainLoop();
  return 0;
}

#pragma endregion
