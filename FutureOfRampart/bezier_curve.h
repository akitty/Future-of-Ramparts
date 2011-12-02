#pragma once
#include <vector>
#include "Vector3.h"
using namespace std;

class bezier_curve
{
public:
	static void generate(int n, vector<Vector3> &v1, int points, vector<vector<Vector3> > &v2 ,vector<vector<Vector3> > &normals);
};