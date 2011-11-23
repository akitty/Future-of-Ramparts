#include "SceneGraph.h"
#include <algorithm>
#include <GL/glut.h>
#include <iostream>
#include "Vector3.h"
using namespace std;
//Node
Node::Node(void){ 
	bounding_radius=0;
	maxtranslation=0;
}
Node::~Node(void){}
//GroupSG
GroupSG::GroupSG(){}
GroupSG::~GroupSG(){}
void GroupSG::addChild(Node * a)
{
	children.push_back(a);
}

//MatrixTransform
MatrixTransform::MatrixTransform()
{
	m1.identity();
}
void MatrixTransform::draw()
{
	glMatrixMode(GL_MODELVIEW);
	//call geode draw
	vector<Node *>::iterator it;
	for(int i =0; i<children.size();i++)
	{
		


		glMatrixMode (GL_MODELVIEW);
		glPushMatrix ();
		
			//cout<<"push"<<endl;
			glMatrixMode(GL_MODELVIEW);
			
			glMultMatrixf(m1.getPointer());	


			//cout<<"draw child"<<endl;
			children[i]->draw();
			//calculat bounding radius
			if(children[i]->bounding_radius>bounding_radius)
			{
				bounding_radius=children[i]->bounding_radius;
			}
			Vector3 v3  = Vector3(m1.m[3][0],m1.m[3][1],m1.m[3][2]);
			float v3len = v3.length();
			if(v3len>maxtranslation)
			{
				maxtranslation=v3len;
			}
			
		glPopMatrix();
		//cout<<"pop"<<endl;

	}
	bounding_radius += maxtranslation;
	
}

void MatrixTransform::applyTransform()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(m1.getPointer());
}
void MatrixTransform::setMatrix(Matrix4 a){m1=a;}

//Geode
Geode::Geode(){
	color.x=0;
	color.y=1;
	color.z=0;}
void Geode::draw(){}
void Geode::setColor(float r,float g,float b) {
	color.x=r;
	color.y=g;
	color.z=b;
}

//sphere
Sphere::Sphere(){radius=1; bounding_radius=1;}
Sphere::Sphere(float r){radius=r; bounding_radius=r;}
void Sphere::draw(){
	glColor3f(color[0],color[1],color[2]);
	
	glutSolidSphere(radius,10,10); 
	//cout<<"draw sphere"<<endl;
}
//cube
Cube::Cube(){length=1; bounding_radius=sqrt(2.0);}
Cube::Cube(float l){length=l;bounding_radius=sqrt(2.0)*l;}
void Cube::draw(){
	//cout<<"draw cube"<<endl;

	glColor3f(color[0],color[1],color[2]);
	glutSolidCube(length);

}
//cylinder
Cylinder::Cylinder(){
	radius=1;
	height=1; 
	bounding_radius=sqrt(radius*radius+height*height*.25);
}
Cylinder::Cylinder(float r, float h){radius=r;height=h;}
void Cylinder::draw(){
	//cout<<"draw cylinder"<<endl;
	//centered at origin
	vector<Vector3> top;
	vector<Vector3> bot;
	int resolution=20;
	double bottom=-height/2.0;
	double topp = height/2.0;
	double theta = 2*3.1415/resolution;
	for(int i =0;i<resolution+1;i++)
	{
		double angle = theta*i;
		double x = cos(angle)*radius;
		double z = sin(angle)*radius;
		top.push_back(Vector3(x,topp,z));
		bot.push_back(Vector3(x,bottom,z));
	}
	for(int i =0; i<resolution;i++)
	{
		
		glBegin(GL_QUADS);
		glColor3f(color[0],color[1],color[2]);
			glVertex3f(top[i][0],top[i][1],top[i][2]);
			glVertex3f(top[i+1][0],top[i+1][1],top[i+1][2]);
			glVertex3f(bot[i+1][0],bot[i+1][1],bot[i+1][2]);
			glVertex3f(bot[i][0],bot[i][1],bot[i][2]);
		glEnd();
	}
}
//torus
Torus::Torus(){
	innerradius=1;
	outerradius=2;
	nsides=5;
	rings=5;
}
Torus::Torus(float inner,float outer,int n,int r){
	innerradius=inner;
	outerradius=outer;
	nsides=n;
	rings=r;
}
void Torus::draw(){
	glutSolidTorus(innerradius,outerradius,nsides,rings);
}


SwitchSG::SwitchSG(int s)
{
	i=0;
	sign=s;
}

void SwitchSG::draw()
{
	i+=sign;
	int limit=45;
	if(abs(i*1.0)>=45)
	{
		sign*=-1;
	}
	//int frame = i%children.size();
	//draw that child
	int a=i;
	glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		glRotatef(a,1,0,0); 
		children[0]->draw();
	glPopMatrix();
}