#include "Cannon.h"


Cannon::Cannon()
{
	Color = Vector3(1,1,1);
	Size = 4.0;
	Center = Vector3(0,0,0);
}

Cannon::Cannon(Vector3 color, float size, Vector3 center)
{
	Color = color;
	Size = size;
	Center = center;
}

void Cannon::render() 
{
  GLUquadric* qobj = gluNewQuadric();
  //gluQuadricNormals(qobj, GLU_SMOOTH);
  float wheel_trans = Size/CUBE_SCALE;

  glColor3d(Color.x, Color.y, Color.z);
  // draw the wheels
  glPushMatrix();

  // make the cannon appear above the ground
  glTranslatef(0, Size/SPHERE_SCALE, 0);

  glutSolidSphere(Size/SPHERE_SCALE, 20, 20);  
  glTranslatef(wheel_trans, 0, 0);
  glutSolidSphere(Size/SPHERE_SCALE, 20, 20);

  // draw the body
  glTranslatef(-wheel_trans/2.0, (Size/SPHERE_SCALE) + (Size/CUBE_SCALE/2), 0);
  glutSolidCube(Size/CUBE_SCALE);

  // draw the opening
  glTranslatef(0, Size/CUBE_SCALE/2 + Size/CYLINDER_RADIUS, 0);
  gluCylinder(qobj, Size/CYLINDER_RADIUS, Size/CYLINDER_RADIUS, Size/CYLINDER_HEIGHT, 20, 20);

  // canonball for testing
  glTranslatef(0, 0, Size/CYLINDER_HEIGHT + Size/CYLINDER_RADIUS);
  glutSolidSphere(Size/CYLINDER_RADIUS, 20, 20);

  glPopMatrix();
  gluDeleteQuadric(qobj);
}
