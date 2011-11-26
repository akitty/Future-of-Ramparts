#pragma once
#include "Geode.h"
#include <vector>
#include <gl\glut.h>

// the standard cube size throughout the game
const float BLOCK_SIZE = 1.0f;
// the height in which the block resides when it's
// waiting to be placed
const float PLACE_HEIGHT = 2.0f;

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
    // whether or not this block is still movable
    bool movable;
    // adjacency list for this block
    vector<Block> neighbors;
    // textures for each face of this block, excluding
    // the bottom face because we'll never see it
    GLuint* faceTextures[5];

    /* make a default block */
    Block();

    /* make a block with this color at this position, not movable */
    Block(const Vector3 & pos);

    /* create a block at this default position and allows it to be moved */
    Block(const Vector3 & pos, bool canBePlaced);

    /* Determines whether another block collides with this one */
    bool collides(Vector3 & otherPos);
    /* Determines whether this block touches another block */
    bool touches(Vector3 & otherPos);

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

