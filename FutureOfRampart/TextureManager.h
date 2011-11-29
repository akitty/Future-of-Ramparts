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

    /* combines a grayscale image of an alpha channel for another texture,
     * along with that texture image into a single texture in openGL 
     */
    static char* addAlphaChannel(Image* image, Image* alphaChannel);

    /* takes two textures, one for the alpha channel, and one for the 
     * texture image... combines them using addAlphaChannel, then 
     * loads them into openGL and returns the GLuint
     */
    static GLuint loadAlphaTexture(Image* image, Image* alphaChannel);
};

