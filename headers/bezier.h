#pragma once
#include "Point3D.h"

using namespace std;

namespace BezierCurveMath
{
	class Bezier
	{
	public:
		Bezier();
		~Bezier();

		void calculateCurvePoints(vector<Geometry::Point3D>& controlPoints, vector<Geometry::Point3D>& vertices);
		Geometry::Point3D calculateBezierPoint(vector<Geometry::Point3D>& controlPoints, double t);



	};
}