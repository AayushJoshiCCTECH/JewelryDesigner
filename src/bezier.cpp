#include "stdafx.h"
#include "Bezier.h"
#include "Point3D.h"

#include <cmath>

using namespace std;

BezierCurveMath::Bezier::Bezier() {}
BezierCurveMath::Bezier::~Bezier() {}

Geometry::Point3D BezierCurveMath::Bezier::calculateBezierPoint(vector<Geometry::Point3D>& controlPoints, double t)
{
	int n = controlPoints.size() - 1;
	double x = 0.0, y = 0.0, z = 0.0;

	for (int i = 0; i <= n; ++i)
	{
		double binomialCoefficient = 1.0;
		for (int j = 0; j < i; ++j)
		{
			binomialCoefficient *= (n - j) / (j + 1.0);
		}

		double term = binomialCoefficient * pow(1 - t, n - i) * pow(t, i);
		x += controlPoints[i].x() * term;
		y += controlPoints[i].y() * term;
		z += controlPoints[i].z() * term;
	}
	return Geometry::Point3D(x, y, z);
}

void BezierCurveMath::Bezier::calculateCurvePoints(vector<Geometry::Point3D>& controlPoints, vector<Geometry::Point3D>& vertices)/* std::vector<GLdouble>& colors*/
{
	for (double t = 0; t <= 1; t += 0.01)
	{
		Geometry::Point3D bezierPoint = calculateBezierPoint(controlPoints, t);
		vertices.push_back(bezierPoint);
	}

}

