#include "Vector4.h"
#include <math.h>
#include "Vector3.h"

float Vector4::get(int i) {
	switch (i){
	case 0: return x;
	case 1: return y;
	case 2: return z;
	case 3: return w;
	default: 
		//should throw exception
		return 0;
	}
}

Vector4::Vector4(Vector3&a)
{
  x=a.x; y=a.y; z=a.z; w=1;
}

Vector4 Vector4::operator+(const Vector4&a)const {
	Vector4 b =  Vector4(w+a.w, x+a.x, y+a.y, z+a.z);
	return b;
}

Vector4 Vector4::operator-(const Vector4&a) const {
	Vector4 b =  Vector4(w-a.w, x-a.x, y-a.y, z-a.z);
	return b;
}

float Vector4::operator[](int i) {
	switch (i){
	case 0: return x;
	case 1: return y;
	case 2: return z;
	case 3: return w;
	default: 
		//should throw exception
		return 0;
	}
}

float Vector4::length() {
	return (float)sqrt(w*w+x*x+y*y+z*z);
}