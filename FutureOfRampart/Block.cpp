#include "Block.h"

Block::Block()
{
  position = Vector3(0.0, 0.0, 0.0);
  movable = false;
}

Block::Block(const Vector3 & pos)
{
  movable = false;
  position = Vector3(pos.x, pos.y, pos.z);
}

Block::Block(const Vector3 & pos, bool canBePlaced)
{
  movable = canBePlaced;
  position = Vector3(pos.x, pos.y, pos.z);
}

/* simplest collision detection in history */
bool Block::collides(Vector3 & otherPos)
{
  if(otherPos.x == position.x &&
    otherPos.z == position.z)
    return true;
  return false;
}

/* also very simple detection */
bool Block::touches(Vector3 & otherPos)
{
  if(otherPos.x != position.x &&
     otherPos.z != position.z)
     return false;
  if(otherPos.x == position.x)
  {
    int zdiff = otherPos.z - position.z;
    if(zdiff == -1 || zdiff == 1)
      return true;
  }
  // the z's are equal
  else
  {
    int xdiff = otherPos.x - position.x;
    if(xdiff == -1 || xdiff == 1)
      return true;
  }
}

void Block::place()
{
  position.y -= PLACE_HEIGHT;
  movable = false;
}

void Block::moveUp()
{
  if(movable)
    position.z -= BLOCK_SIZE;
}

void Block::moveDown()
{
  if(movable)
    position.z += BLOCK_SIZE;
}

void Block::moveLeft()
{
  if(movable)
    position.x -= BLOCK_SIZE;
}

void Block::moveRight()
{
  if(movable)
    position.x += BLOCK_SIZE;
}

/* A somewhat difficult member function.
  We need to draw this block one face at a time
  in order to texture properly */
void Block::render()
{
  // DEBUGGING FUNCTIONALITY
  glPushMatrix();
    glColor3f(0.0, 1.0, 0.0);
    glTranslatef(position.x, position.y, position.z);
    glutSolidCube(BLOCK_SIZE);
  glPopMatrix();
}
