#include "Map.h"
#include "TextureNumbers.h"


Map::Map(GLuint textureNums[])
{
  // initialize all of the base blocks of this world
  for(int i = 0; i < MAP_HEIGHT; ++i)
  {
    for(int j = 0; j < MAP_WIDTH; ++j)
    {
      // set the blocks at the given position, 
      // and non-movable
      base[i][j] = Block(Vector3(i, 0, j),
                         textureNums[MAP_TOP_BASE],
                         textureNums[MAP_FRONT],
                         textureNums[MAP_BACK],
                         textureNums[MAP_LEFT],
                         textureNums[MAP_RIGHT],
                         textureNums[MAP_TOP_BASE],
                         false);
    }
  }
}

void Map::draw(Matrix4 & m)
{
  // save the current matrix
  glPushMatrix();

  glMatrixMode(GL_MODELVIEW);
  Matrix4 tf(m);

  // camera rotations to the map affect all blocks inside
  glLoadMatrixf(tf.getPointer());

  for(int i = 0; i < MAP_HEIGHT; ++i)
  {
    for(int j = 0; j < MAP_WIDTH; ++j)
    {
      // draw this particular block
      base[i][j].draw(m);
    }
  }

  // reset the current matrix
  glPopMatrix();
}
