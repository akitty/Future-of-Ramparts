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
#include "Player.h"
#include <ctime>

using namespace std;

#pragma region GAME_GLOBALS
// The frames per second we'll use for this game
const float FPS = 10; // 50 fps
const float numUpdates = 1500/FPS; // number of updates to reach 1.5 seconds

/* fps related stuff */
static int frames = 0;
static float totalfps = 0.0f;

// set window width in pixels here
int Window::width  = 1024;   
// set window height in pixels here
int Window::height = 768;
// The matrix that defines world rotations
Matrix4 worldMatrix; 
// PLAYER 1
Player* player1;
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
Matrix4 cannonball;
MatrixTransform cannonball_trans;
MatrixTransform block_trans;
Matrix4 block_mat;
MatrixTransform mat;
Block b;
Cannon c;
Sphere s;
bool stop = false;
bool fire = false;

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
void updateVelocity(Sphere & s);

#pragma endregion

#pragma region GAME_HANDLE_INPUT


void updateVelocity(Sphere & s)
{
	s.Velocity = Vector3(s.Velocity[0], s.Velocity[1] + GRAVITY, s.Velocity[2]);
	s.Center = s.Center + s.Velocity;
	cannonball.translate(s.Center);
	cannonball_trans.setTransformation(cannonball);
}

void updateBezierPosition(Sphere & s)
{
	s.updatePosition();
	cannonball.translate(s.Center);
	cannonball_trans.setTransformation(cannonball);
}


/**
 * Some keyboard routines to handle turning the spot and point lights
 * on and off.
 */
void handleInput(unsigned char key, int, int)
{
  camera.handleInput(key, 0, 0);
  if(player1 != NULL)
	  player1->handleInputs(key);
  //Player2.handleInput(key);
  if(key == 'p')
  {
	  player1->giveBlock();
  }
  if(key == 'k')
  {
	  if(!isExploding)
	  {
		  explosion = new Explosion(Vector3(2.0, 2.0, 2.0));
		  isExploding = true;
		  world.addChild(explosion);
	  }
  }
  /* James test code */
  /*********************/
  
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
  // fire cannonball
  if(key == 'f')
  {
	  fire = !fire;
  }
  

  /*********************/
}

#pragma endregion

#pragma region GAME_INIT

/* initialize the scene graph for the game */
void initializeMap()
{
/*	
  gameMap = new Map(textureNums);
  world.addChild(gameMap);

  testBlock = new Block(Vector3(4.0f, BLOCK_SIZE, 4.0f), BLOCK_TOP, BLOCK_FRONT, BLOCK_BACK, BLOCK_LEFT, BLOCK_RIGHT, BLOCK_RIGHT, false);
  world.addChild(testBlock);
 
   char keys[6];


  keys[0] = 'z';
  keys[1] = 'x';
  keys[2] = 'c';
  keys[3] = 'v';
  keys[4] = 'b';
  keys[5] = 'n';
  player1 = new Player(4, 4, -10, 10, -10, 10, keys, MAP_TOP_P1);
  if(player1 != NULL)
	world.addChild(player1);
  */
  Vector3 displacement = Vector3(10, 2, 20);
  block_mat.translate(displacement);
  block_trans.setTransformation(block_mat);

  world.addChild(&rotate_trans);
  rotate_trans.addChild(&c);
  s = c.fire();
  cannonball.translate(s.Center);
  cannonball_trans.setTransformation(cannonball);
  rotate_trans.addChild(&cannonball_trans);
  rotate_trans.addChild(&block_trans);
  block_trans.addChild(&b);
  cannonball_trans.addChild(&s);

  b.center = b.center + displacement;
  //  s.calcInitialVelocity(b);
  s.calcBezierPath(b);

  
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
  eye.y = 40.0f;
  eye.z = 40.0f; 
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

/*********************/
  

  glutPostRedisplay();
}

/* 
 * Update the positions of the projectiles and such.
 */
void update(int value)
{
	if(s.collidesWithBlock(b, false)) {
	  if (!intersect) {
		  cout << "interesection! collision at point number " << s.position << ": " << s.bezier_points[0][s.position] << "\n";
		  intersect = true;
		  s.collidesWithBlock(b, true);
		  
		  explosion = new Explosion(b.center);
		  isExploding = true;
		  world.addChild(explosion);

		  block_trans.removeChild(&b);
		  cannonball_trans.removeChild(&s);

		  
	  }
  } 
	if(fire) updateBezierPosition(s);
	glutTimerFunc(FPS, update, 0);
}

#pragma endregion

#pragma region GAME_DRAW

void Window::displayCallback()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // rotate camera
  //worldMatrix.multiply(eye);
  // set the new look-at point
  gluLookAt(eye.x, eye.y, eye.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  clock_t before = clock();

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

    //cout << "FPS: " << fps << endl;

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
  // 10 miliseconds
  glutTimerFunc(FPS, update, 0);

  glutMainLoop();
  return 0;
}

#pragma endregion
