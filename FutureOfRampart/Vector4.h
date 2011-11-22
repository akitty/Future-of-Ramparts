#ifndef _VECTOR4_
#define _VECTOR4_
#include <iostream>
#include "Vector3.h"
class Vector4 {
public:
  float w,x,y,z;
	Vector4() {w=x=y=z=0;}
	Vector4(float x0,float y0,float z0,float w0)	{w=w0; x=x0; y=y0; z=z0;}
  Vector4(Vector3&);
	void set( float x0,float y0,float z0,float w0) {w=w0; x=x0; y=y0; z=z0;}
	float get(int);

	Vector4 operator+(const Vector4& ) const;
	float operator[](int);
	Vector4 operator-(const Vector4&)const;
  Vector4 operator*(float a) {
    return Vector4(x*a,y*a,z*a,w*a);
  }

  Vector4 operator/(float a) const{
    if(a==0.0)
    {
      cerr<<"Divide by 0 error"<<endl;
    }
    float oneOverA=1.0f/a;
    
    return Vector4(x*oneOverA,y*oneOverA,z*oneOverA,w*oneOverA);
  }
	float dot(Vector4& a) {return w*a.w+x*a.x+y*a.y+z*a.z;}



	float length();

	void normalize() { 
    float length=this->length();
    if(length>0.0f)
    {
      *this=*this/length;
    }
  }

	void dehomogenize()
	{
		if(w>0.0f)
		{
			x=x/w;
      y=y/w;
      z=z/w;
      w=1;
		}
    else
      std::cout<<"dehomogenize error divide by 0"<<std::endl;
		
	}

};

inline float vectorMag(const Vector4&a)
{
  return sqrt(a.x*a.x+a.y*a.y*a.z*a.z*a.w*a.w);
}




#endif