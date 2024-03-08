	#include "stdafx.h"
	#include "Bezier.h"
	#include "Point3D.h"

	#include <cmath>

	BezierCurveMath::Bezier::Bezier() {}
	BezierCurveMath::Bezier::~Bezier() {}


	/*void BezierCurveMath::Bezier::calculateCurvePoints(QVector<Geometry::Point3D>& controlPoints, QVector<double>& inCoordinates)
	{
	    double power = controlPoints.size() - 1;
	
	    for (double t = 0; t <= 1; t += 0.1)
	    {
	        double x = 0.0;
	        double y = 0.0;
	        double z = 0.0;
	
	        for (double i = 0.0; i < controlPoints.size(); i++)
	        {
	            x += pow(1 - t, power - i) * pow(t, i) * controlPoints[i].x();
	            y += pow(1 - t, power - i) * pow(t, i) * controlPoints[i].y();
	            z += pow(1 - t, power - i) * pow(t, i) * controlPoints[i].z();
	        }
	
	        inCoordinates.push_back(x);
	        inCoordinates.push_back(y);
	        inCoordinates.push_back(z);
	    }
	}*/


	Geometry::Point3D BezierCurveMath::Bezier::calculateBezierPoint(QVector<Geometry::Point3D>& controlPoints, double t)
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

	void BezierCurveMath::Bezier::calculateCurvePoints(QVector<Geometry::Point3D>& controlPoints, QVector<double>& vertices)/* std::vector<GLdouble>& colors*/
	{
		for (double t = 0; t <= 1; t += 0.01)
		{
			Geometry::Point3D bezierPoint = calculateBezierPoint(controlPoints, t);
			vertices.push_back(bezierPoint.x());
			vertices.push_back(bezierPoint.y());
			vertices.push_back(bezierPoint.z());		
		}

	}

