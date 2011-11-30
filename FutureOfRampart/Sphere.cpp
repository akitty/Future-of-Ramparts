#include "Sphere.h"
#include <GL/glut.h>

Sphere::Sphere(Vector3 & params, Vector3 & color, Vector3 & center, Vector3 & velocity, Vector3 & scale, bool wire)
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

  Center.x = center.x;
  Center.y = center.y;
  Center.z = center.z;

  Velocity.x = velocity.x;
  Velocity.y = velocity.y;
  Velocity.z = velocity.z;
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

  Center = Vector3(0,0,0);
  Velocity = Vector3(0,0,0);
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

/* Collision testing, sphere and cube
 * find closest point on cube to sphere.
 * if distance between that point and center of sphere is less than or equal to radius, there is collision.
 */
bool Sphere::collidesWithBlock(Block & b, bool test) 
{
  // Get the center of the sphere relative to the center of the box
  Vector3 sphereCenterRelBox = Center - b.center;
  // Point on surface of box that is closest to the center of the sphere
  Vector3 boxPoint;
  // Check sphere center against box along the X axis alone. 
  // If the sphere is off past the left edge of the box, 
  // then the left edge is closest to the sphere. 
  // Similar if it's past the right edge. If it's between 
  // the left and right edges, then the sphere's own X 
  // is closest, because that makes the X distance 0, 
  // and you can't get much closer than that :)

  if (sphereCenterRelBox.x < -(BLOCK_SIZE/2.0))
	boxPoint.x = -(BLOCK_SIZE/2.0);
  else if (sphereCenterRelBox.x > BLOCK_SIZE/2.0)
	boxPoint.x = BLOCK_SIZE/2.0;
  else
	boxPoint.x = sphereCenterRelBox.x;

  // ...same for Y axis
  if (sphereCenterRelBox.y < -(BLOCK_SIZE/2.0)) boxPoint.y = -(BLOCK_SIZE/2.0);
  else if (sphereCenterRelBox.y > BLOCK_SIZE/2.0) boxPoint.y = BLOCK_SIZE/2.0;
  else boxPoint.y = sphereCenterRelBox.y;

  // ... same for Z axis
  if (sphereCenterRelBox.z < -(BLOCK_SIZE/2.0)) boxPoint.z = -(BLOCK_SIZE/2.0);
  else if (sphereCenterRelBox.z > BLOCK_SIZE/2.0) boxPoint.z = BLOCK_SIZE/2.0;
  else boxPoint.z = sphereCenterRelBox.z;

  // Now we have the closest point on the box, so get the distance from 
  // that to the sphere center, and see if it's less than the radius


  Vector3 dist = sphereCenterRelBox - boxPoint;
  float distVal = (dist.x*dist.x + dist.y*dist.y + dist.z*dist.z);

  if(test) 
  {
	cout << "sphere at position " << Center << "\n";
	cout << "block at position " << b.center << "\n";
	cout << sphereCenterRelBox << " is the position that the sphere center is in relation to the box \n";
	cout << boxPoint << " is the closest point on the box to the sphere with respect to the box's center \n";
	cout << distVal << "units from center of sphere \n";
  }

  // if the distance from the closest point on the cube to the sphere is
  // less than the radius of the sphere, there has been a colission.
  if (distVal < 1) 
	return true;
  else
	return false;
}