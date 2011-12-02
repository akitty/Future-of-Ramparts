#include "Sphere.h"

Sphere::Sphere(Vector3 & center)
{
  Center.x = center.x;
  Center.y = center.y;
  Center.z = center.z;

  // 75 when making 2 paths
  //bezier_normals = vector<vector<Vector3>>(2,vector<Vector3>());
  //bezier_points = vector<vector<Vector3>>(2,vector<Vector3>());

  position = 0;
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
	cout << "sphere at position " << Center << "\n";
	cout << "block at position " << b.center << "\n";
	cout << sphereCenterRelBox << " is the position that the sphere center is in relation to the box \n";
	cout << boxPoint << " is the closest point on the box to the sphere with respect to the box's center \n";
	cout << distVal << "units from center of sphere \n";
  }

  // if the distance from the closest point on the cube to the sphere is
  // less than the radius of the sphere, there has been a colission.
  if (distVal < (CYLINDER_RADIUS*CYLINDER_RADIUS)) 
	return true;
  else
	return false;
}

// calculate the initial velocity vector for the sphere to collide with the block
// we will assume there is an update every 10ms and collision occurs in 1.5 seconds.
// assume a gravity constant
void Sphere::calcInitialVelocity(Block & b) {
							// this will be a const value declared elsewhere
	float updates = 150;    // number of updates to occur before collision, 1.5 seconds/ update frequency

	float maxGravity = GRAVITY*updates; // the gravitational effect at the time of collision

	// the sphere location with the middle of the box's top surface as the origin
	// the vector3 is the offset from the center of the block to the center of the top
	Vector3 sphereCenterRelBox = (b.center + Vector3(0,BLOCK_SIZE,0)) - Center; 

	Vector3 temp = b.center + Vector3(0,BLOCK_SIZE,0);

	// if the sphere traveled in a straight line, this is w/o gravitation effect
	Vector3 velocityWithoutGravity = Vector3(sphereCenterRelBox[0]/updates, 
											sphereCenterRelBox[1]/updates, 
											sphereCenterRelBox[2]/updates);
	cout << "firing at location " << "{" << temp[0] << ", " << temp[1] << ", " << temp[2] << "}\n";
	cout << "from location " << "{" << Center[0] << ", " << Center[1] << ", " << Center[2] << "}\n";
	cout << "without gravity " << velocityWithoutGravity[0] << ", " << velocityWithoutGravity[1] << ", " << velocityWithoutGravity[2] << "\n";

	// convert line into a curve to change y velocity to take into account gravity
	Vector3 velocityWithGravity = Vector3(velocityWithoutGravity[0], 
										velocityWithoutGravity[1] - maxGravity/2.0, 
										velocityWithoutGravity[2]);

	Velocity = velocityWithGravity;

}

void Sphere::calcBezierPath(Block & b) {
							// this will be a const value declared elsewhere
	float updates = 150;    // number of updates to occur before collision, 1.5 seconds/ update frequency

	// the sphere location with the middle of the box's top surface as the origin
	// the vector3 is the offset from the center of the block to the center of the top
//	Vector3 sphereCenterRelBox = (b.center + Vector3(0,BLOCK_SIZE,0)) - Center; 

	vector<Vector3> pointset = vector<Vector3>(7, Vector3());

	Vector3 endpoint = b.center /* Vector3(0,BLOCK_SIZE,0)*/;


	pointset[0] = Center;
	pointset[1] = Center + Vector3(-5,-5,-5);
	pointset[2] = Center + Vector3(5,5,5);
	pointset[3] = Vector3(endpoint[0]/2.0, endpoint[1]/2.0, endpoint[2]/2.0);
	pointset[4] = Center + Vector3(5,5,5);
	pointset[5] = Center - Vector3(5,5,5);
	pointset[6] = endpoint;

	// make a bezier curve with 2 pieces
	bezier_curve::generate(2, pointset, 150, bezier_points, bezier_normals);
}

void Sphere::updatePosition() 
{
//	cout << "made it here \n";
//	cout << bezier_points.size() << " sets of bezier points\n";
//	cout << bezier_points[0].size() << " bezier points in plot 1\n";
//	cout << bezier_points[1].size() << " bezier points in plot 2\n";
//	if(position < 75) Center = bezier_points[0][position];
//	else Center = bezier_points[1][position-75];

//	cout << "at position " << position << "\n";

	if(position <= 150) Center = bezier_points[0][position];
	position++;
}