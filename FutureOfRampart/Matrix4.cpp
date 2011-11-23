
#include "Matrix4.h"
#include <math.h>
#include <iostream>
using namespace std;
Matrix4::Matrix4()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      if(i == j)
        m[i][j] = 1;
      m[i][j] = 0;
    }
  }
} 
//column major
/*

m00 m10 m20 m30
m01
m02         m32
m03     m23 m33  

*/
Matrix4::Matrix4(
  float m00, float m01, float m02, float m03,
  float m10, float m11, float m12, float m13,
  float m20, float m21, float m22, float m23,
  float m30, float m31, float m32, float m33 )
{
  m[0][0] = m00;
  m[0][1] = m01;
  m[0][2] = m02;
  m[0][3] = m03;

  m[1][0] = m10;
  m[1][1] = m11;
  m[1][2] = m12;
  m[1][3] = m13;

  m[2][0] = m20;
  m[2][1] = m21;
  m[2][2] = m22;
  m[2][3] = m23;

  m[3][0] = m30;
  m[3][1] = m31;
  m[3][2] = m32;
  m[3][3] = m33;
}

Matrix4::Matrix4(Vector4&a,Vector4&b,Vector4&c,Vector4&d)
{
  m[0][0] = a[0];
  m[0][1] = a[1];
  m[0][2] = a[2];
  m[0][3] = a[3];

  m[1][0] = b[0];
  m[1][1] = b[1];
  m[1][2] = b[2];
  m[1][3] = b[3];

  m[2][0] = c[0];
  m[2][1] = c[1];
  m[2][2] = c[2];
  m[2][3] = c[3];

  m[3][0] = d[0];
  m[3][1] = d[1];
  m[3][2] = d[2];
  m[3][3] = d[3];
}

float* Matrix4::getPointer()
{
  return &m[0][0];
}

void Matrix4::identity()
{
  float ident[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = ident[i][j];
    }
  }
}



void Matrix4::multiply(Matrix4& b)
{
	//store old matrix values
	int nums[]={00,01,02,03,10,11,12,13,20,21,22,23,30,31,32,33};
	Matrix4 a=Matrix4();
	for(int i =0;i<16;i++)
	{
		a.set(nums[i],get(nums[i]));
	}
	m[0][0] = b.m[0][0]*a.m[0][0]+b.m[0][1]*a.m[1][0]+b.m[0][2]*a.m[2][0]+b.m[0][3]*a.m[3][0];
	m[0][1] = b.m[0][0]*a.m[0][1]+b.m[0][1]*a.m[1][1]+b.m[0][2]*a.m[2][1]+b.m[0][3]*a.m[3][1];
	m[0][2] = b.m[0][0]*a.m[0][2]+b.m[0][1]*a.m[1][2]+b.m[0][2]*a.m[2][2]+b.m[0][3]*a.m[3][2];
	m[0][3] = b.m[0][0]*a.m[0][3]+b.m[0][1]*a.m[1][3]+b.m[0][2]*a.m[2][3]+b.m[0][3]*a.m[3][3];
	
	m[1][0] = b.m[1][0]*a.m[0][0]+b.m[1][1]*a.m[1][0]+b.m[1][2]*a.m[2][0]+b.m[1][3]*a.m[3][0];
	m[1][1] = b.m[1][0]*a.m[0][1]+b.m[1][1]*a.m[1][1]+b.m[1][2]*a.m[2][1]+b.m[1][3]*a.m[3][1];
	m[1][2] = b.m[1][0]*a.m[0][2]+b.m[1][1]*a.m[1][2]+b.m[1][2]*a.m[2][2]+b.m[1][3]*a.m[3][2];
	m[1][3] = b.m[1][0]*a.m[0][3]+b.m[1][1]*a.m[1][3]+b.m[1][2]*a.m[2][3]+b.m[1][3]*a.m[3][3];
	
	m[2][0] = b.m[2][0]*a.m[0][0]+b.m[2][1]*a.m[1][0]+b.m[2][2]*a.m[2][0]+b.m[2][3]*a.m[3][0];
	m[2][1] = b.m[2][0]*a.m[0][1]+b.m[2][1]*a.m[1][1]+b.m[2][2]*a.m[2][1]+b.m[2][3]*a.m[3][1];
	m[2][2] = b.m[2][0]*a.m[0][2]+b.m[2][1]*a.m[1][2]+b.m[2][2]*a.m[2][2]+b.m[2][3]*a.m[3][2];
	m[2][3] = b.m[2][0]*a.m[0][3]+b.m[2][1]*a.m[1][3]+b.m[2][2]*a.m[2][3]+b.m[2][3]*a.m[3][3];
	
	m[3][0] = b.m[3][0]*a.m[0][0]+b.m[3][1]*a.m[1][0]+b.m[3][2]*a.m[2][0]+b.m[3][3]*a.m[3][0];
	m[3][1] = b.m[3][0]*a.m[0][1]+b.m[3][1]*a.m[1][1]+b.m[3][2]*a.m[2][1]+b.m[3][3]*a.m[3][1];
	m[3][2] = b.m[3][0]*a.m[0][2]+b.m[3][1]*a.m[1][2]+b.m[3][2]*a.m[2][2]+b.m[3][3]*a.m[3][2];
	m[3][3] = b.m[3][0]*a.m[0][3]+b.m[3][1]*a.m[1][3]+b.m[3][2]*a.m[2][3]+b.m[3][3]*a.m[3][3];



}
/*
*Multiplys a vector4 with this matrix and modifies the vector4
*
**/
void Matrix4::multiply(Vector4& a) {
	//dot each row of the matrix with the column vector a
	Vector4 r=Vector4();
	float result[4];
	for(int i = 0; i <4;i++)
	{
		row(i,r);
		result[i]=r.dot(a);
	}
	a.set(result[0],result[1],result[2],result[3]);
	return;
}

void Matrix4::multiply(Vector3& a) {
	// extend a with 1
	//dot each row with the column vector a
	Vector4 v4 = Vector4(a[0],a[1],a[2],1);
	multiply(v4);
	v4.dehomogenize();
	a.set(v4[0],v4[1],v4[2]);
	return;

}


void Matrix4::row(int i,Vector4&a){
	float row[4];
	for(int j=0;j<4;j++)
	{
		row[j]=this->m[j][i];
	}
	a.set(row[0],row[1],row[2],row[3]);
	return;
}

void Matrix4::column(int j,Vector4&a){
	float col[4];
	for(int i=0;i<4;i++)
	{
		col[i]=this->m[i][j];
	}
	a.set(col[0],col[1],col[2],col[3]);
	return;
}

void Matrix4::rotatex(float t){
	//change t from deg to radians
	t=t*0.01745329;
	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = cos(t);
	m[1][2] = sin(t);
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = -sin(t);
	m[2][2] = cos(t);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;


}


void Matrix4::rotatey(float t){
	//change t from deg to radians
	t=t*0.01745329;
	m[0][0] = cos(t);
	m[0][1] = 0;
	m[0][2] = -sin(t);
	m[0][3] = 0;

	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = 0;

	m[2][0] = sin(t);
	m[2][1] = 0;
	m[2][2] = cos(t);
	m[2][3] = 0;

	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}
void Matrix4::rotatez(float t){
	//change t from deg to radians
	t=t*0.01745329;
	m[0][0] = cos(t);
	m[0][1] = sin(t);
	m[0][2] = 0;
	m[0][3] = 0;
	
	m[1][0] = -sin(t);
	m[1][1] = cos(t);
	m[1][2] = 0;
	m[1][3] = 0;
	
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = 0;
	
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

void Matrix4::rotate(Vector3& v, float t){
	
	//normalize v
	v.normalize();
	float c=cos(t);
	float s=sin(t);
	m[0][0] = v[0]*v[0]+c*(1- v[0]*v[0]);
	m[0][1] = v[0]*v[1]*(1-c)+v[2]*s;
	m[0][2] = v[0]*v[2]*(1-c)-v[1]*s;
	m[0][3] = 0;
	
	m[1][0] = v[0]*v[1]*(1-c)-v[2]*s;
	m[1][1] = v[1]*v[1]+c*(1- v[1]*v[1]);
	m[1][2] = v[1]*v[2]*(1-c)+v[0]*s;
	m[1][3] = 0;
	
	m[2][0] = v[0]*v[2]*(1-c)+v[1]*s;
	m[2][1] = v[2]*v[3]*(1-c)-v[0]*s;
	m[2][2] = v[2]*v[2]+c*(1- v[2]*v[2]);
	m[2][3] = 0;
	
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

void Matrix4::rotateDeg(Vector3& v, double t){
	t=t*0.01745329;
	//normalize v
	v.normalize();
	float c=cos(t);
	float s=sin(t);
	m[0][0] = v[0]*v[0]+c*(1- v[0]*v[0]);
	m[0][1] = v[0]*v[1]*(1-c)+v[2]*s;
	m[0][2] = v[0]*v[2]*(1-c)-v[1]*s;
	m[0][3] = 0;
	
	m[1][0] = v[0]*v[1]*(1-c)-v[2]*s;
	m[1][1] = v[1]*v[1]+c*(1- v[1]*v[1]);
	m[1][2] = v[1]*v[2]*(1-c)+v[0]*s;
	m[1][3] = 0;
	
	m[2][0] = v[0]*v[2]*(1-c)+v[1]*s;
	m[2][1] = v[2]*v[3]*(1-c)-v[0]*s;
	m[2][2] = v[2]*v[2]+c*(1- v[2]*v[2]);
	m[2][3] = 0;
	
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

void Matrix4::scale(float x, float y, float z){
	m[0][0] = x;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	
	m[1][0] = 0;
	m[1][1] = y;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	
	m[2][1] = 0;
	m[2][2] = z;
	m[2][3] = 0;
	
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;


}

void Matrix4::scale(Vector3&a){
	scale(a[0],a[1],a[2]);
	return;
}

void Matrix4::translate(float x, float y, float z){
	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = 0;
	
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = 0;
	
	m[3][0] = x;
	m[3][1] = y;
	m[3][2] = z;
	m[3][3] = 1;

}

void Matrix4::shear(float a, float b, float w, float x, float y, float z){
  m[0][0] = 1;
  m[0][1] = a;
  m[0][2] = b;
  m[0][3] = 0;

  m[1][0] = w;
  m[1][1] = 1;
  m[1][2] = x;
  m[1][3] = 0;

  m[2][0] = y;
  m[2][1] = z;
  m[2][2] = 1;
  m[2][3] = 0;

  m[3][0] = 0;
  m[3][1] = 0;
  m[3][2] = 0;
  m[3][3] = 1;
}

void Matrix4::translate(Vector3&a){
	translate(a[0],a[1],a[2]);
}

void Matrix4::set(int i,float a){
	int ones=i%10;
	int tens=i/10;
	m[tens][ones]=a;
}
void Matrix4::set2(int i,float a)
{
	int j,k;
	j=i/4;
	k=i%4;
	m[j][k]=a;
}

float Matrix4::get(int i){
	int ones=i%10;
	int tens=i/10;
	return m[tens][ones];
}



/************************************************************
*
* input:
* mat - pointer to array of 16 floats (source matrix)
* output:
* dst - pointer to array of 16 floats (invert matrix)
*
*************************************************************/
//void invert(float *mat, float *dst)
void Matrix4::invert(Matrix4& dst1)
{
	
	float tmp[12]; /* temp array for pairs */
	float src[16]; /* array of transpose source matrix */
	float det; /* determinant */
	
	float *mat=getPointer();
	//float * mat = &m[0][0];
	float * dst= &dst1.m[0][0];
	/* transpose matrix */

	for (int i = 0; i < 4; i++) {
		src[i] = mat[i*4];
	src[i + 4] = mat[i*4 + 1];
	src[i + 8] = mat[i*4 + 2];
	src[i + 12] = mat[i*4 + 3];
	}

	/* calculate pairs for first 8 elements (cofactors) */
	tmp[0] = src[10] * src[15];
	tmp[1] = src[11] * src[14];
	tmp[2] = src[9] * src[15];
	tmp[3] = src[11] * src[13];
	tmp[4] = src[9] * src[14];
	tmp[5] = src[10] * src[13];
	tmp[6] = src[8] * src[15];
	tmp[7] = src[11] * src[12];
	tmp[8] = src[8] * src[14];
	tmp[9] = src[10] * src[12];
	tmp[10] = src[8] * src[13];
	tmp[11] = src[9] * src[12];
	/* calculate first 8 elements (cofactors) */
	dst[0] = tmp[0]*src[5] + tmp[3]*src[6] + tmp[4]*src[7];
	dst[0] -= tmp[1]*src[5] + tmp[2]*src[6] + tmp[5]*src[7];
	dst[1] = tmp[1]*src[4] + tmp[6]*src[6] + tmp[9]*src[7];
	dst[1] -= tmp[0]*src[4] + tmp[7]*src[6] + tmp[8]*src[7];
	dst[2] = tmp[2]*src[4] + tmp[7]*src[5] + tmp[10]*src[7];
	dst[2] -= tmp[3]*src[4] + tmp[6]*src[5] + tmp[11]*src[7];
	dst[3] = tmp[5]*src[4] + tmp[8]*src[5] + tmp[11]*src[6];
	dst[3] -= tmp[4]*src[4] + tmp[9]*src[5] + tmp[10]*src[6];
	dst[4] = tmp[1]*src[1] + tmp[2]*src[2] + tmp[5]*src[3];
	dst[4] -= tmp[0]*src[1] + tmp[3]*src[2] + tmp[4]*src[3];
	dst[5] = tmp[0]*src[0] + tmp[7]*src[2] + tmp[8]*src[3];
	dst[5] -= tmp[1]*src[0] + tmp[6]*src[2] + tmp[9]*src[3];
	dst[6] = tmp[3]*src[0] + tmp[6]*src[1] + tmp[11]*src[3];
	dst[6] -= tmp[2]*src[0] + tmp[7]*src[1] + tmp[10]*src[3];
	dst[7] = tmp[4]*src[0] + tmp[9]*src[1] + tmp[10]*src[2];
	dst[7] -= tmp[5]*src[0] + tmp[8]*src[1] + tmp[11]*src[2];
	/* calculate pairs for second 8 elements (cofactors) */
	tmp[0] = src[2]*src[7];
	tmp[1] = src[3]*src[6];
	tmp[2] = src[1]*src[7];
	tmp[3] = src[3]*src[5];
	tmp[4] = src[1]*src[6];
	tmp[5] = src[2]*src[5];
	tmp[6] = src[0]*src[7];
	tmp[7] = src[3]*src[4];
	tmp[8] = src[0]*src[6];
	tmp[9] = src[2]*src[4];
	tmp[10] = src[0]*src[5];
	tmp[11] = src[1]*src[4];
	/* calculate second 8 elements (cofactors) */
	dst[8] = tmp[0]*src[13] + tmp[3]*src[14] + tmp[4]*src[15];
	dst[8] -= tmp[1]*src[13] + tmp[2]*src[14] + tmp[5]*src[15];
	dst[9] = tmp[1]*src[12] + tmp[6]*src[14] + tmp[9]*src[15];
	dst[9] -= tmp[0]*src[12] + tmp[7]*src[14] + tmp[8]*src[15];
	dst[10] = tmp[2]*src[12] + tmp[7]*src[13] + tmp[10]*src[15];
	dst[10]-= tmp[3]*src[12] + tmp[6]*src[13] + tmp[11]*src[15];
	dst[11] = tmp[5]*src[12] + tmp[8]*src[13] + tmp[11]*src[14];
	dst[11]-= tmp[4]*src[12] + tmp[9]*src[13] + tmp[10]*src[14];
	dst[12] = tmp[2]*src[10] + tmp[5]*src[11] + tmp[1]*src[9];
	dst[12]-= tmp[4]*src[11] + tmp[0]*src[9] + tmp[3]*src[10];
	dst[13] = tmp[8]*src[11] + tmp[0]*src[8] + tmp[7]*src[10];
	dst[13]-= tmp[6]*src[10] + tmp[9]*src[11] + tmp[1]*src[8];
	dst[14] = tmp[6]*src[9] + tmp[11]*src[11] + tmp[3]*src[8];
	dst[14]-= tmp[10]*src[11] + tmp[2]*src[8] + tmp[7]*src[9];
	dst[15] = tmp[10]*src[10] + tmp[4]*src[8] + tmp[9]*src[9];
	dst[15]-= tmp[8]*src[9] + tmp[11]*src[10] + tmp[5]*src[8];
	/* calculate determinant */
	det=src[0]*dst[0]+src[1]*dst[1]+src[2]*dst[2]+src[3]*dst[3];
	/* calculate matrix inverse */
	det = 1/det;
	for (int j = 0; j < 16; j++)
	dst[j] *= det;
	
}

void Matrix4::viewport(int x0,int x1,int y0, int y1)
{
  m[0][0] = (x1-x0)/2;
  m[0][1] = 0;
  m[0][2] = 0;
  m[0][3] = 0;

  m[1][0] = 0;
  m[1][1] = (y1-y0)/2;
  m[1][2] = 0;
  m[1][3] = 0;

  m[2][0] = 0;
  m[2][1] = 0;
  m[2][2] = 0.5;
  m[2][3] = 0;

  m[3][0] = (x0+x1)/2;
  m[3][1] = (y0+y1)/2;
  m[3][2] = 0.5;
  m[3][3] = 1;

}

void Matrix4::print()
{

	for(int i =0;i<4;i++)
	{
			cout<<"\n";
		for(int j=0;j<4;j++)
		{
		
		 cout<<m[j][i]<< "  ";
		}
		
	}
	cout<<endl;

}
