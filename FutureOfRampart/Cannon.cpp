#include "Cannon.h"

Cannon::Cannon(Vector3 center)
{

	Center = center + Vector3(WHEEL_HEIGHT + (BODY_SIZE + XOFFSET)/2.0,
							(CYLINDER_YZ_TRANSLATION + BODY_SIZE/2.0 + CYLINDER_RADIUS + YOFFSET)/2.0,
							(CYLINDER_YZ_TRANSLATION + BODY_SIZE/2.0)/2.0);

	CannonballInitialCenter = Vector3(Center[0],
									Center[1]*2.0 + 2.0*CANNONBALL_YZ_TRANSLATION + BLOCK_SIZE,
									Center[2]*2.0 + 2.0*CANNONBALL_YZ_TRANSLATION + ZOFFSET);
}

Sphere Cannon::fire()
{
	return Sphere(CannonballInitialCenter);
}

void Cannon::render() 
{
  GLUquadric* qobj = gluNewQuadric();
  //gluQuadricNormals(qobj, GLU_SMOOTH);

  glColor3f(0.0, 0.0, 0.0);

  // draw the wheels
  glPushMatrix();

  // make the cannon appear above the ground
  glTranslatef(0, WHEEL_RADIUS+BLOCK_SIZE, ZOFFSET);
  glRotatef(90, 0,1,0);
  gluCylinder(qobj, WHEEL_RADIUS, WHEEL_RADIUS, WHEEL_HEIGHT, 20, 20); 
  glRotatef(-90, 0,1,0);
  glTranslatef(BODY_SIZE + WHEEL_RADIUS, 0, 0);
  glRotatef(90, 0,1,0);
  gluCylinder(qobj, WHEEL_RADIUS, WHEEL_RADIUS, WHEEL_HEIGHT, 20, 20); 
  glRotatef(-90, 0,1,0);

  // draw the body
  glTranslatef(-BODY_SIZE/2.0, BODY_SIZE/2, 0);
  glColor3f(.5451, .2706, .0745);
  glutSolidCube(BODY_SIZE);

  // draw the opening
  glTranslatef(0, CYLINDER_RADIUS, BODY_SIZE/2.0);
  glColor3f(0.0, 0.0, 0.0);
  glRotatef(-45, 1,0,0);
  gluCylinder(qobj, CYLINDER_RADIUS, CYLINDER_RADIUS, CYLINDER_HEIGHT, 20, 20);

  // canonball for testing
//  glTranslatef(0, 0, CYLINDER_HEIGHT + CYLINDER_RADIUS);

//  glutSolidSphere(CYLINDER_RADIUS, 20, 20);

  glPopMatrix();
  gluDeleteQuadric(qobj);
}
