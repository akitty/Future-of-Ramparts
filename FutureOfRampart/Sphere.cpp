#include "Sphere.h"
#include <GL/glut.h>

Sphere::Sphere(Vector3 & params, Vector3 & color, Vector3 & scale, bool wire)
{
  Params.x = params.x;
  Params.y = params.y;
  Params.z = params.z;

  Color.x = color.x;
  Color.y = color.y;
  Color.z = color.z;

  if(scale.x == 1.0 &&
    scale.y == 1.0 &&
    scale.z == 1.0)
  {
    scaled = false;
  }
  else
  {
    scaled = true;
    Scale.x = scale.x;
    Scale.y = scale.y;
    Scale.z = Scale.z;
  }
  Wire = wire;
}

Sphere::Sphere()
{
  Params.x = 1.0;
  Params.y = 20;
  Params.z = 20;

  Color.x = 1.0;
  Color.y = 1.0;
  Color.z = 1.0;

  scaled = false;

  Wire = false;
}

void Sphere::render()
{
  if(scaled)
  {
    glPushMatrix;
    glScalef(Scale.x, Scale.y, Scale.z);
  }
  glColor3d(Color.x, Color.y, Color.z);

  if(!Wire)
    glutSolidSphere(Params.x, Params.y, Params.z);
  else
    glutWireSphere(Params.x, Params.y, Params.z);

  if(scaled)
    glPopMatrix;
}
