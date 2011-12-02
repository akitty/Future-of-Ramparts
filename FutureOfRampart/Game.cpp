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
#include "ParticleEngine.h"
#include "Map.h"
#include <ctime>

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
ParticleEngine* explosion;
bool isExploding = false;

/* James test code */
/*********************/
bool intersect = false;
Matrix4 m;
MatrixTransform mat;
Sphere s = Sphere(Vector3(1.0, 20, 20), Vector3(1.0, 1.0, 1.0), Vector3(-10.0, 0, 0), Vector3(.01, .072, 0));
Block b;
Cannon c;
const float gravity = -.0001;
bool stop = false;

float xincre = 0.0; bool xrot = false;
float yincre = 0.0; bool yrot = false;
float zincre = 0.0; bool zrot = false;
float amount = .15;

Matrix4 i;
Matrix4 x;
Matrix4 y;
Matrix4 z;
Matrix4 rotate_matrix;
MatrixTransform rotate_trans;

Matrix4 tran;
MatrixTransform tosurface = MatrixTransform(tran);
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
  if(key == 'e')
  {
    isExploding = true;
    glutTimerFunc(TIMER_MS, update, 0);
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
  // x
  if(key == 'b')
  {
	xrot = !xrot;
  }
  // y
  if(key == 'n')
  {
	yrot = !yrot;
  }
  // z
  if(key == 'm')
  {
	zrot = !zrot;
  }
  /*
  // create block
  if(key == 'o')
  {
	block();
  }
  // place block
  if(key == 'p')
  {
	zrot = !zrot;
  }
  */
  /*********************/
}

#pragma endregion

#pragma region GAME_INIT

/* initialize the scene graph for the game */
void initializeMap()
{
  gameMap = new Map(textureNums);
//  world.addChild(gameMap);

  /* James test code */
  /*********************/
//  m.translate(s.Center); 
//  mat.setTransformation(m);
//  world.addChild(&mat);
//  world.addChild(&b);
//  mat.addChild(&s);
//  tran.translate(20,-20,-20);
//  world.addChild(&rotate_trans);
//  world.addChild(gameMap);
//  gameMap->player1.addChild(&rotate_trans);
  world.addChild(&rotate_trans);

  rotate_trans.addChild(&c);

//  world.addChild(&c)

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

  for(int i = 0; i < NUM_TEXTURES - NUM_MISC_TEXTURES; ++i)
  {
    // load each one in
    TextureManager::loadTexture(textures[i], textureNums[i]);
  }

  // BEGIN LOADING MISCELLANEOUS TEXTURES
  Image* image = loadBMP("circle.bmp");
	Image* alphaChannel = loadBMP("circlealpha.bmp");

	textureNums[NUM_TEXTURES - 1] = TextureManager::loadAlphaTexture(image, alphaChannel);
	delete image;
	delete alphaChannel;
}

void initializeExplosion()
{
  explosion = new ParticleEngine(Vector3(2.0,2.0,2.0), 100, CIRCLE_COMB, 20, BLOCK_SIZE);
  explosion->initialize();
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
/* James test code */
/*********************/
	/*
 if(s.collidesWithBlock(b, false)) {
	  if (!intersect) {
		  cout << "interesection! \n";
		  intersect = true;
		  s.collidesWithBlock(b, true);
		  
	  }
  } */

	if(xrot) xincre+=amount;
	if(yrot) yincre+=amount;
	if(zrot) zincre+=amount;

	x = i;
	y = i;
	z = i;
	rotate_matrix = i;

	x.rotatex(xincre);
	y.rotatey(yincre);
	z.rotatez(zincre);

	rotate_matrix.multiply(x);
	rotate_matrix.multiply(y);
	rotate_matrix.multiply(z);

	rotate_trans.setTransformation(rotate_matrix);





//  if(!stop) cout << s.Center << "\n";

  m.translate(s.Center);
  mat.setTransformation(m);
  s.Velocity.set(s.Velocity[0], s.Velocity[1] + gravity, s.Velocity[2]);
  s.Center = s.Center + s.Velocity;
/*********************/

  Window::displayCallback();
}


/*
 * particles will fade out in proportion with duration.
 * particle velocity and movement updating should be scaled to the bounding
 * radius.
 * we want to also subtract the gravity constraint each time to the 
 * particles' trajectory so that it eventually falls.
 */
void update(int value)
{
  /* timer processing */
  explosion->advance(TIMER_MS / 1000.0f);
	glutPostRedisplay();

  /* recall update after specified milliseconds have passed */
  glutTimerFunc(TIMER_MS, update, 0);
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
  srand((unsigned int)time(0)); //Seed the random number generator

  glutInit(&argc, argv);      	      	  
  // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
  glutInitWindowSize(Window::width, Window::height);      
  glutCreateWindow("Future of Rampart");  

  glEnable(GL_DEPTH_TEST);                // enable depth buffering
  glClearColor(0.3, 0.5, 1.0, 1.0);   	  // set clear color to black
	glEnable(GL_BLEND);
	glEnable(GL_COLOR_MATERIAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
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
  initializeExplosion();

  glutMainLoop();
  return 0;
}

#pragma endregion
