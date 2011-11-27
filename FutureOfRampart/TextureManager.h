#pragma once
#include <gl\glut.h>
#include "imageloader.h"
#include "TextureNumbers.h"

class TextureManager
{
  public:
    /* handles switching one texture image for another for drawing */
    static void subTexture(GLuint textureId);

    /* handles binding a texture to a textureId within openGL */
    static void loadTexture(Image* image, GLuint textureId);
};

