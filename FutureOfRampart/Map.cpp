#include "Map.h"


Map::Map()
{
  // initialize all of the base blocks of this world
  for(int i = 0; i < MAP_HEIGHT; ++i)
  {
    for(int j = 0; j < MAP_WIDTH; ++j)
    {
      // set the blocks at the given position, 
      // and non-movable
      base[i][j] = Block(Vector3(i, 0, j));
    }
  }
}

void Map::draw(Matrix4 & m)
{
  glPushMatrix();

  glMatrixMode(GL_MODELVIEW);
  Matrix4 tf(m);
  

  for(int i = 0; i < MAP_HEIGHT; ++i)
  {
    for(int j = 0; j < MAP_WIDTH; ++j)
    {
      // draw all of the blocks inside base
      glLoadMatrixf(tf.getPointer());
      base[i][j].draw(m);
      glPopMatrix();
    }
  }
}
