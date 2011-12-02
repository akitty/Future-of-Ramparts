#pragma once
#include "Geode.h"
#include <vector>
#include <gl\glut.h>

// the standard cube size throughout the game
const float BLOCK_SIZE = 2.0f;

// the height in which the block resides when it's
// waiting to be placed
const float PLACE_HEIGHT = 2.0f;
const int NUM_FACES   = 6;
const int FACE_POINTS = 4;

const int BACKFACE    = 0;
const int BOTTOMFACE  = 1;
const int TOPFACE     = 2;
const int LEFTFACE    = 3;
const int RIGHTFACE   = 4;
const int FRONTFACE   = 5;

/**
 * This is the generalized Block within our game.
 *
 * It has variables and methods associated with it
 * to make things easier to work with. 
 */
class Block : public Geode
{
  public:
    // position of this cube in the game
    Vector3 position;
	// position of the center in the cube 
	// for collission detection
	//Vector3 center;
    // whether or not this block is still movable
    bool movable;
    // adjacency list for this block
    vector<Block> neighbors;
    // textures for each face of this block, excluding
    // the bottom face because we'll never see it
    GLuint faceTextures[NUM_FACES];
    // normals and vertices for this cube
    Vector3 normals[NUM_FACES];
    Vector3 vertices[NUM_FACES][FACE_POINTS];
    bool isTextured;

    /* make a default block */
    Block();

    /* make a block with this color at this position, not movable */
    Block(const Vector3 & pos);

    /* create a block at this default position and allows it to be moved */
    Block(const Vector3 & pos, bool canBePlaced);

    /* create a block passing in these textures */
    Block(const Vector3 & pos, GLuint top, GLuint front, 
          GLuint back, GLuint left, GLuint right, GLuint bottom, bool canBePlaced);

    /* Determines whether another block collides with this one */
    bool collides(Vector3 & otherPos);
    /* Determines whether this block touches another block */
    bool touches(Vector3 & otherPos);

    /* create the normal vectors and vertices for this cube */
    void generate();

    /* switches the texture for this block's top face with the new GLuint */
    void switchTopFace(GLuint newFace);

    /* Called when the player places the block or gameBlock associated with
      this block object. The final result is that the block is moved down
      to game level and is no longer movable */
    void place();

    /* control moving around the blocks */
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    /* render the block at this position */
    void render();
};

