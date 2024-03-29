#include "Map.h"
#include "TextureNumbers.h"

Map::Map(GLuint textureNums[])
{
  // initialize all of the base blocks of this world
  for(int i = 0; i < MAP_HEIGHT / 2; ++i)
  {
    for(int j = 0; j < MAP_WIDTH / 2; ++j)
	{
	  int bX = i*BLOCK_SIZE;
	  int bZ = j*BLOCK_SIZE;
	  int nbX = -i*BLOCK_SIZE;

      // QUADRANT 1 (i, j)
      base[i][j] = Block(Vector3(bX, 0, bZ),
                         textureNums[MAP_TOP_BASE],
                         textureNums[MAP_FRONT],
                         textureNums[MAP_BACK],
                         textureNums[MAP_LEFT],
                         textureNums[MAP_RIGHT],
                         textureNums[MAP_TOP_BASE],
                         false);
      // QUADRANT 2 (-i, j)
      base[i + MAP_HEIGHT / 2][j] = Block(Vector3(nbX, 0, bZ),
                         textureNums[MAP_TOP_BASE],
                         textureNums[MAP_FRONT],
                         textureNums[MAP_BACK],
                         textureNums[MAP_LEFT],
                         textureNums[MAP_RIGHT],
                         textureNums[MAP_TOP_BASE],
                         false);
    }
  }

  for(int i = 0; i < MAP_HEIGHT / 2; ++i)
  {
    for(int j = 0; j < MAP_WIDTH / 2; ++j)
    {
	  int bX = i*BLOCK_SIZE;
	  int nbX = -i*BLOCK_SIZE;
	  int nbZ = -j*BLOCK_SIZE;

      // set the blocks at the given position, 
      // and non-movable
      // QUADRANT 3 (-i, -j)
      base[i + MAP_HEIGHT / 2][j + MAP_WIDTH / 2] = Block(Vector3(nbX, 0, nbZ),
                         textureNums[MAP_TOP_BASE],
                         textureNums[MAP_FRONT],
                         textureNums[MAP_BACK],
                         textureNums[MAP_LEFT],
                         textureNums[MAP_RIGHT],
                         textureNums[MAP_TOP_BASE],
                         false);
      // QUADRANT 4 (i, -j)
      base[i][j + MAP_WIDTH / 2] = Block(Vector3(bX, 0, nbZ),
                         textureNums[MAP_TOP_BASE],
                         textureNums[MAP_FRONT],
                         textureNums[MAP_BACK],
                         textureNums[MAP_LEFT],
                         textureNums[MAP_RIGHT],
                         textureNums[MAP_TOP_BASE],
                         false);
    }
  }

  drawn = false;
}

void Map::draw(Matrix4 & m)
{
  // save the current matrix
  glPushMatrix();

  glMatrixMode(GL_MODELVIEW);
  Matrix4 tf(m);

  // camera rotations to the map affect all blocks inside
  glLoadMatrixf(tf.getPointer());

  if(!drawn)
  {
    GAME_MAP = glGenLists(1);
    glNewList(GAME_MAP, GL_COMPILE);

    for(int i = 0; i < MAP_HEIGHT; ++i)
    {
      for(int j = 0; j < MAP_WIDTH; ++j)
      {
        // draw this particular block
        base[i][j].draw(m);
      }
    }

    glEndList();

    drawn = true;
  }
  else
  {
    glCallList(GAME_MAP);
  }

  // render player stuff
  std::list<Node*>::iterator nodes;

  for(nodes = children.begin(); nodes != children.end(); ++nodes)
  {
    (*nodes)->draw(m);
  }

  // reset the current matrix
  glPopMatrix();
}
