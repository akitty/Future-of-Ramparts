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
#include "Explosion.h"
#include "Map.h"
#include <ctime>

using namespace std;

#pragma region GAME_GLOBALS
// The frames per second we'll use for this game
const float FPS = 10; // 50 fps

/* fps related stuff */
static int frames = 0;
static float totalfps = 0.0f;

// set window width in pixels here
int Window::width  = 1024;   
// set window height in pixels here
int Window::height = 768;
// The matrix that defines world rotations
Matrix4 worldMatrix; 
// The central camera function that modifies the world matrix
IsoCamera camera(worldMatrix); 
// the scene graph for the world
SGGroup world;
// a pointer to the game map
Map* gameMap;
// a test block for debugging purposes
Block* testBlock;
// the textures we'll use
Image* textures[NUM_TEXTURES];
// the numbers of these textures
GLuint textureNums[NUM_TEXTURES];
// a particle engine
Explosion* explosion;
// whether or not the engine is exploding
bool isExploding = false;
Vector3 eye;

/* James test code */
/*********************/
bool intersect = false;
Matrix4 m;
MatrixTransform mat;
Sphere s = Sphere(Vector3(1.0, 20, 20), Vector3(1.0, 1.0, 1.0), Vector3(-10.0, 0, 0), Vector3(.01, .072, 0));
Block b;
const float gravity = -.0001;
bool stop = false;
/*********************/

#pragma endregion

#pragma region GAME_PROTOTYPES

void update(int value);
bool collidesWith(Sphere s, Block b, bool test);

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
  if(key == 'k')
  {
    explosion = new Explosion(Vector3(2.0, 2.0, 2.0));
    isExploding = true;
    world.addChild(explosion);
    //gameMap->player1.addChild(explosion);
  }
  /* James test code */
  /*********************/
  if(key == 'r')
  {
	  intersect = false;
	  s.Velocity.set(.01, .072, 0);
	  stop = false;
	  s.Center.set(-10, 0, 0);
  }
  if(key == 'c')
  {
	  stop = true;
	  s.Velocity.set(0,0,0);
  }
  /*********************/
}

#pragma endregion

#pragma region GAME_INIT

/* initialize the scene graph for the game */
void initializeMap()
{
  gameMap = new Map(textureNums);
  world.addChild(gameMap);

  /* James test code */
  /*********************/
  //m.translate(s.Center); 
  //mat.setTransformation(m);
  //world.addChild(&mat);
  //world.addChild(&b);
  //mat.addChild(&s);
  /*********************/
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

  // 0-11
  for(int i = 0; i < NUM_TEXTURES - NUM_MISC_TEXTURES; ++i)
  {
    // load each one in
    TextureManager::loadTexture(textures[i], textureNums[i]);
  }

  // BEGIN LOADING MISCELLANEOUS TEXTURES
  Image* image = loadBMP("Smoke_Texture.bmp");
	Image* alphaChannel = loadBMP("Smoke_Texture_Grayscale.bmp");

  // 12
	textureNums[EXPLOSION] = TextureManager::loadAlphaTexture(image, alphaChannel);

	delete image;
	delete alphaChannel;
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
  eye.x = 0.0f;
  eye.y = 50.0f;
  eye.z = 30.0f; 
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
/* James test code */
/*********************/
  /*
 if(s.collidesWithBlock(b, false)) {
	  if (!intersect) {
		  //cout << "interesection! \n";
		  intersect = true;
		  s.collidesWithBlock(b, true);
		  
	  }
  }

//  if(!stop) cout << s.Center << "\n";

  m.translate(s.Center);
  mat.setTransformation(m);
  s.Velocity.set(s.Velocity[0], s.Velocity[1] + gravity, s.Velocity[2]);
  s.Center = s.Center + s.Velocity;
/*********************/
  

  glutPostRedisplay();
}

#pragma endregion

#pragma region GAME_DRAW

void Window::displayCallback()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // rotate camera
  worldMatrix.multiply(eye);
  // set the new look-at point
  gluLookAt(eye.x, eye.y, eye.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  clock_t before = clock();

  // game scene graph
  worldMatrix.identity();
  world.draw(worldMatrix);

  if(isExploding)
  {
    if(explosion->done)
    {
      world.removeChild(explosion);
      delete explosion;
      isExploding = false;
    }
  }

  glutSwapBuffers();

    clock_t after = clock();

  totalfps += 1.0f / ((float)(after - before) / CLOCKS_PER_SEC);
    
  frames++;

  if(frames == 25)
  {
    float fps = totalfps / 25.0;

    cout << "FPS: " << fps << endl;

    totalfps = 0.0f;
    frames = 0;
  }
}

#pragma endregion

#pragma region OpenGL_Initialization

int main(int argc, char *argv[])
{
  srand((unsigned int)time(0)); //Seed the random number generator

  glutInit(&argc, argv);      	      	  
  // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
  glutInitWindowSize(Window::width, Window::height);      
  glutCreateWindow("Future of Rampart");  

  glEnable(GL_DEPTH_TEST);                // enable depth buffering
  glClearColor(0.3, 0.5, 0.7, 1.0);   	  // set clear color to sky blue
	glEnable(GL_COLOR_MATERIAL);
  
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
