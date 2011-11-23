#pragma once
#include <vector>
#include "Matrix4.h"
#include "Vector3.h"
using namespace std;

class Node
{
public:
	Node();
	float bounding_radius;
	float maxtranslation;
	virtual ~Node(void);
	virtual void draw()=0;
};

class GroupSG :public Node
{
public:
	GroupSG();
	virtual ~GroupSG() ;
	virtual void draw()=0;
	void addChild(Node*);
	

	
	vector<Node *> children;
	
};



class MatrixTransform : public GroupSG
{
public:
	Matrix4 m1;
	MatrixTransform();
	~MatrixTransform(){}
	void draw();
	void applyTransform();
	void setMatrix(Matrix4);
	//void addChild(Node *);
	
};





class SwitchSG :
	public GroupSG
{
public:
	SwitchSG(int s);
	
	 void draw();
	 int sign;
	 int i;
};

class Geode : public Node
{
public:
	Geode(void);
	virtual void draw()=0;
	Vector3 color;
	void setColor(float,float,float);
};

class Sphere: public Geode
{
private:
	float radius;
public:
  Sphere();
  Sphere(float r);
    void draw();
};

class Cube: public Geode
{
private:
	float length;
public:
	Cube();
	Cube(float l);
	
	 void draw();
};

class Cylinder: public Geode
{
private:
	float radius,height;
public:
	Cylinder();
	Cylinder(float r, float h);
	 void draw();
};

class Torus:public Geode
{
private:
	float innerradius,outerradius;
	int nsides,rings;
public:
	Torus();
	Torus(float,float,int,int);
	void draw();
};

