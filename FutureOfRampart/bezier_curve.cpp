#include "bezier_curve.h"
#include "Vector4.h"
#include "Matrix4.h"

// v1 is point set, v2 is, normals is
void bezier_curve::generate(int n, vector<Vector3> &v1, int points, vector<vector<Vector3> > &v2 ,vector<vector<Vector3>> &normals)
{

  //make c1 continuous
  //joining control points are at 3,4,5
  //at i*4-1 to i*4+1
  if(v1.size()!=n*4-n+1)
    cerr<<"error:size of v1 not equal to number of segments"<<endl;
  //should i assume correct positioning?
  
  int points_per_section=points/n;
   v2.push_back(vector<Vector3>());
   normals.push_back(vector<Vector3>());
  // v2.back().push_back(v1[0]);
  for(int i =0;i<4+(n-1)*3-1;i+=3)
  {

    //piecewise evaluation
    Vector3 p0,p1,p2,p3;
    //Matrix4 t;
    
    //calculat section points
    //push onto vector
    for(int j = 0 ; j < points_per_section;j++)
    {

      p0=Vector3(v1[i]);
      p1=Vector3(v1[i+1]);
      p2=Vector3(v1[i+2]);
      p3=Vector3(v1[i+3]);
      float t = 1.0/points_per_section*j;
      
        Vector3 x=p0*(-t*t*t+3*t*t-3*t+1)+
                p1*(3*t*t*t-6*t*t+3*t)+
                p2*(-3*t*t*t+3*t*t)+
                p3*t*t*t;
       
        v2.back().push_back(x);
        Vector3 tangent = Vector3(
          p0*(-3*t*t+6*t-3)+
          p1*(3*(1-t)*(1-t)-6*(1-t)*t)+
          p2*(6*(1-t)*t-3*t*t)+
          p3*3*t*t
          );
        Vector3 normalV = Vector3(-tangent.y,tangent.x,0);
        normalV.normalize();
        normals.back().push_back(normalV);
    }
  }
    Vector3 end=v1.back();
    v2.back().push_back(end);

}