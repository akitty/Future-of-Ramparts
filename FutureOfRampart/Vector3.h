#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include "math.h"

#include <iostream>
using namespace std;

class Vector3 {
	friend ostream & operator<<(ostream& output,  Vector3& v){ 
	output << "x:"<<v.x<<" y:"<<v.y<<" z:"<<v.z;
		return output;
	}
	
public:
	float x,y,z;
	Vector3() {x=y=z=0;}
	Vector3(float x0,float y0,float z0)	{x=x0; y=y0; z=z0;}
  Vector3(const Vector3 &a):x(a.x),y(a.y),z(a.z) {}

  Vector3 & operator=(const Vector3&a){
    x=a.x; y=a.y; z=a.z;
    return *this;
  }

	void set(float x0,float y0,float z0) {x=x0; y=y0; z=z0;}
	float get(int);
	void add(Vector3 &a)	{x=x+a.x;y=y+a.y;z=z+a.z;}
	Vector3 add(Vector3&a,Vector3&b)	{Vector3* v = new Vector3(a.x+b.x,a.y+b.y,a.z+b.z); return *v;}
	Vector3 operator+(Vector3& );
	float operator[](int);
	Vector3 operator-(Vector3&);
  //check for equality
  bool operator==(const Vector3&a) const{ 
    return x==a.x&&y==a.y&&z==a.z;
  }
  bool operator!=(const Vector3&a) const {
    return x!=a.x||y!=a.y||z!=a.z;
  }
  Vector3 operator*(float a)
  {
    return Vector3(a*x,a*y,a*z);
  }
  Vector3 operator*(Vector3&a)
  {
	return Vector3(y*a.z-z*a.y,z*a.x-x*a.z,x*a.y-y*a.x);
  }
  
	void sub(Vector3& a) {x=x-a.x; y=y-a.y; z=z-a.z;}
	Vector3& sub(Vector3& a,Vector3& b) {Vector3* v = new Vector3(a.x-b.x,a.y-b.y,a.z-b.z); return *v;}
	void scalar(float s) {x=x*s; y=y*s; z=z*s;}
	float dot(Vector3& a) {return x*a.x+y*a.y+z*a.z;}
	static float dot(Vector3&a,Vector3&b) { return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];}
	void cross(Vector3&); 
	static void cross(Vector3&,Vector3&,Vector3&);
  static Vector3& cross(Vector3&, Vector3&);
	float length();
	void normalize() { scalar(1.0f/length()); }
	void print();
	float angle(Vector3&a)
	{
		return acos(this->dot(a)/(this->length()*a.length()));
	}
};


#endif