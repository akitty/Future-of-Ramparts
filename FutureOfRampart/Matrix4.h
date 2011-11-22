#pragma once
#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "Vector4.h"
#include "Vector3.h"

class Matrix4
{
protected:
  public:
	float m[4][4];   // matrix elements
    Matrix4();        // constructor
    Matrix4(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);
    Matrix4(Vector4&a,Vector4&b,Vector4&c,Vector4&d);
    float* getPointer();  // return pointer to matrix elements
    void identity();  // create identity matrix
    
   
	void set(int,float);
	float get(int);
	void multiply(Matrix4&);
	void multiply(Vector4&);
	void multiply(Vector3&);
	void row(int,Vector4&);
	void column(int,Vector4&);
	void rotatex(float);
	void rotatey(float);
	void rotatez(float);
  void viewport(int, int,int,int);
	void rotate(Vector3&,float);
	void rotateDeg(Vector3&,double);
	void scale(float,float,float);
	void scale(Vector3&);
	void translate(float,float,float);
	void translate(Vector3&);
	void shear(float, float, float, float, float, float);
	void invert(Matrix4& );
	void print();
	void set2(int,float);

};

#endif