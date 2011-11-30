#include "Block.h"
#include "TextureManager.h"
#include <iostream>

using namespace std;

Block::Block()
{
  position = Vector3(0.0, 0.0, 0.0);
  center = Vector3(2.0, 2.0, -2.0);
  movable = false;
  isTextured = false;
  generate();
}

Block::Block(const Vector3 & pos)
{
  movable = false;
  isTextured = false;
  position = Vector3(pos.x, pos.y, pos.z);
  center = Vector3(pos.x + 2.0, + pos.y + 2.0, pos.z - 2.0);
  generate();
}

Block::Block(const Vector3 & pos, bool canBePlaced)
{
  movable = canBePlaced;
  isTextured = false;
  position = Vector3(pos.x, pos.y, pos.z);
  center = Vector3(pos.x + 2.0, + pos.y + 2.0, pos.z - 2.0);
  generate();
}

Block::Block(const Vector3 & pos, GLuint top, GLuint front, GLuint back,
             GLuint left, GLuint right, GLuint bottom, bool canBePlaced)
{
  movable = canBePlaced;
  position = Vector3(pos.x, pos.y, pos.z);
  center = Vector3(pos.x + 2.0, + pos.y + 2.0, pos.z - 2.0);
       
  faceTextures[BACKFACE]    = back;
  faceTextures[BOTTOMFACE]  = bottom;
  faceTextures[TOPFACE]     = top;
  faceTextures[LEFTFACE]    = left;
  faceTextures[RIGHTFACE]   = right;
  faceTextures[FRONTFACE]   = front;
  
  isTextured = true;
  generate();
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
  return false;
}

void Block::place()
{
  position.y -= PLACE_HEIGHT;
  center.y -= PLACE_HEIGHT;
  movable = false;
}

void Block::moveUp()
{
  if(movable)
    position.z -= BLOCK_SIZE;
    center.z -= BLOCK_SIZE;
}

void Block::moveDown()
{
  if(movable)
    position.z += BLOCK_SIZE;
    center.z += BLOCK_SIZE;
}

void Block::moveLeft()
{
  if(movable)
    position.x -= BLOCK_SIZE;
    center.x -= BLOCK_SIZE;
}

void Block::moveRight()
{
  if(movable)
    position.x += BLOCK_SIZE;
    center.x += BLOCK_SIZE;
}

/* swap the top face with the new one */
void Block::switchTopFace(GLuint newFace)
{
  faceTextures[5] = newFace;
}

/**
 * Algorithm to generate all of the vertices and normals
 * for each face of this cube. This simplifies 
 * the rendering process as well as texturing.
 */
void Block::generate()
{
  // back face
  vertices[BACKFACE][0] = Vector3(0.0, 0.0, -BLOCK_SIZE);
  vertices[BACKFACE][1] = Vector3(BLOCK_SIZE, 0.0, -BLOCK_SIZE);
  vertices[BACKFACE][2] = Vector3(BLOCK_SIZE, BLOCK_SIZE, -BLOCK_SIZE);
  vertices[BACKFACE][3] = Vector3(0.0, BLOCK_SIZE, -BLOCK_SIZE);
  normals[BACKFACE]  = Vector3::cross((vertices[0][1] - vertices[0][0]), (vertices[0][3] - vertices[0][0]));

  // bottom face
  vertices[BOTTOMFACE][0] = Vector3(0.0, 0.0, 0.0);
  vertices[BOTTOMFACE][1] = Vector3(BLOCK_SIZE, 0.0, 0.0);
  vertices[BOTTOMFACE][2] = Vector3(BLOCK_SIZE, 0.0, -BLOCK_SIZE);
  vertices[BOTTOMFACE][3] = Vector3(0.0, 0.0, -BLOCK_SIZE);
  normals[BOTTOMFACE] = Vector3::cross((vertices[1][1] - vertices[1][0]), (vertices[1][3] - vertices[1][0]));

  // top face
  vertices[TOPFACE][0] = Vector3(0.0, BLOCK_SIZE, 0.0);
  vertices[TOPFACE][1] = Vector3(BLOCK_SIZE, BLOCK_SIZE, 0.0);
  vertices[TOPFACE][2] = Vector3(BLOCK_SIZE, BLOCK_SIZE, -BLOCK_SIZE);
  vertices[TOPFACE][3] = Vector3(0.0, BLOCK_SIZE, -BLOCK_SIZE);
  normals[TOPFACE] = Vector3::cross((vertices[2][1] - vertices[2][0]), (vertices[2][3] - vertices[2][0]));

  // left face
  vertices[LEFTFACE][0] = Vector3(0.0, 0.0, 0.0);
  vertices[LEFTFACE][1] = Vector3(0.0, 0.0, -BLOCK_SIZE);
  vertices[LEFTFACE][2] = Vector3(0.0, BLOCK_SIZE, -BLOCK_SIZE);
  vertices[LEFTFACE][3] = Vector3(0.0, BLOCK_SIZE, 0.0);
  normals[LEFTFACE] = Vector3::cross((vertices[3][1] - vertices[3][0]), (vertices[3][3] - vertices[3][0]));

  // right face
  vertices[RIGHTFACE][0] = Vector3(BLOCK_SIZE, 0.0, 0.0);
  vertices[RIGHTFACE][1] = Vector3(BLOCK_SIZE, 0.0, -BLOCK_SIZE);
  vertices[RIGHTFACE][2] = Vector3(BLOCK_SIZE, BLOCK_SIZE, -BLOCK_SIZE);
  vertices[RIGHTFACE][3] = Vector3(BLOCK_SIZE, BLOCK_SIZE, 0.0);
  normals[RIGHTFACE] = Vector3::cross((vertices[4][1] - vertices[4][0]), (vertices[4][3] - vertices[4][0]));

  // front face
  vertices[FRONTFACE][0] = Vector3(0.0, 0.0, 0.0);
  vertices[FRONTFACE][1] = Vector3(BLOCK_SIZE, 0.0, 0.0);
  vertices[FRONTFACE][2] = Vector3(BLOCK_SIZE, BLOCK_SIZE, 0.0);
  vertices[FRONTFACE][3] = Vector3(0.0, BLOCK_SIZE, 0.0);
  normals[FRONTFACE] = Vector3::cross((vertices[5][1] - vertices[5][0]), (vertices[5][3] - vertices[5][0]));

  //DEBUG
  //Vector3(0.0, 0.0, 0.0); // 0
  //Vector3(BLOCK_SIZE, 0.0, 0.0); // 1
  //Vector3(0.0, BLOCK_SIZE, 0.0); // 2
  //Vector3(BLOCK_SIZE, BLOCK_SIZE, 0.0); // 3
  //Vector3(0.0, 0.0, -BLOCK_SIZE); // 4
  //Vector3(BLOCK_SIZE, 0.0, -BLOCK_SIZE); // 5
  //Vector3(0.0, BLOCK_SIZE, -BLOCK_SIZE); // 6
  //Vector3(BLOCK_SIZE, BLOCK_SIZE, -BLOCK_SIZE); // 7
}

/* draw one face at a time and texture in as needed */
void Block::render()
{
  glPushMatrix();

    // move the block to its relative position
    glTranslatef(position.x, position.y, position.z);

    if(isTextured) glEnable(GL_TEXTURE_2D);

    // for each face
    for(int i = 0; i < NUM_FACES; ++i)
    {
      // bind appropriate texture, if enabled
      if(isTextured) TextureManager::subTexture(faceTextures[i]);

      glBegin(GL_QUADS);
        // set face normal
        glNormal3f(normals[i].x, normals[i].y, normals[i].z);
        // draw face vertices as well as texCoords if they're enabled
        if(isTextured) glTexCoord2f(0.0f, 0.0f);
        glVertex3f(vertices[i][0].x, vertices[i][0].y, vertices[i][0].z);
        if(isTextured) glTexCoord2f(1.0f, 0.0f);
        glVertex3f(vertices[i][1].x, vertices[i][1].y, vertices[i][1].z);
        if(isTextured) glTexCoord2f(1.0f, 1.0f);
        glVertex3f(vertices[i][2].x, vertices[i][2].y, vertices[i][2].z);
        if(isTextured) glTexCoord2f(0.0f, 1.0f);
        glVertex3f(vertices[i][3].x, vertices[i][3].y, vertices[i][3].z);
      glEnd();
    }

  glPopMatrix();
}
