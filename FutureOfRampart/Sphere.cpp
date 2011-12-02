#include "Sphere.h"

Sphere::Sphere(Vector3 & center)
{
  Center.x = center.x;
  Center.y = center.y;
  Center.z = center.z;
}

void Sphere::render()
{
  glColor3f(0.0, 0.0, 0.0);


  glutSolidSphere(CYLINDER_RADIUS, 20, 20);
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
	//cout << "sphere at position " << Center << "\n";
	//cout << "block at position " << b.center << "\n";
	//cout << sphereCenterRelBox << " is the position that the sphere center is in relation to the box \n";
	//cout << boxPoint << " is the closest point on the box to the sphere with respect to the box's center \n";
	//cout << distVal << "units from center of sphere \n";
  }

  // if the distance from the closest point on the cube to the sphere is
  // less than the radius of the sphere, there has been a colission.
  if (distVal < 1) 
	return true;
  else
	return false;
}

// calculate the initial velocity vector for the sphere to collide with the block
// we will assume there is an update every 10ms and collision occurs in 1.5 seconds.
// assume a gravity constant
void Sphere::calcInitialVelocity(Block & b) {
	float gravity = -.0001;	  // this will be a const value declared elsewhere
	float updates = 500;    // number of updates to occur before collision, 1.5 seconds/ update frequency

	float maxGravity = gravity*updates; // the gravitational effect at the time of collision

	// the sphere location with the middle of the box's top surface as the origin
	// the vector3 is the offset from the center of the block to the center of the top
	Vector3 sphereCenterRelBox = Center - (b.center + Vector3(0,2,0)); 

	// if the sphere traveled in a straight line, this is w/o gravitation effect
	Vector3 velocityWithoutGravity = Vector3(sphereCenterRelBox[0]/updates, 
											sphereCenterRelBox[1]/updates, 
											sphereCenterRelBox[2]/updates);

	// convert line into a curve to change y velocity to take into account gravity
	Vector3 velocityWithGravity = Vector3(velocityWithoutGravity[0], 
										velocityWithoutGravity[1] - maxGravity/2.0, 
										velocityWithoutGravity[2]);

	Velocity = velocityWithGravity;

}
