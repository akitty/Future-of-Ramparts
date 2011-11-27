
#include "Vector3.h"
//#include <iostream>
//using namespace std;




float Vector3::get(int a) {
	
	switch (a) {
	case 0:
		return x;
		break;
	case 1:
		return y;
		break;
	case 2:
		return z;
		break;
	default:
		//should throw exception
		return 0;

	}
	
}

Vector3 Vector3::operator+(Vector3&a){
	Vector3 b =  Vector3(x+a.x,y+a.y,z+a.z);
	return b;
}


Vector3 Vector3::operator-(Vector3&a){
	Vector3 b =  Vector3(x-a.x,y-a.y,z-a.z);
	return b;
}

float Vector3::operator[](int i) {
	switch (i){
	case 0: return x;
	case 1: return y;
	case 2: return z;
	default: 
		//should throw exception
		return 0;
	}
}

Vector3& Vector3::cross(Vector3& left, Vector3& right)
{
  Vector3 result;
  cross(result, left, right);
  return result;
}

void Vector3::cross(Vector3& a){
	float xt,yt,zt;
	xt=x;
	yt=y;
	zt=z;
	x= yt*a.z-zt*a.y;
	y= zt*a.x-xt*a.z;
	z= xt*a.y-yt*a.x;
}

void  Vector3::cross(Vector3& result,Vector3&a,Vector3&b)  
{
	result.x=a.y*b.z-a.z*b.y;
	result.y= a.z*b.x-a.x*b.z;
	result.z= a.x*b.y-a.y*b.x;
}


float Vector3::length() {
	return (float)sqrt(x*x+y*y+z*z);
}

