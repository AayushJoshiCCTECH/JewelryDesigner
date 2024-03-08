#pragma once
#include "Point3D.h"

namespace BezierCurveMath
{
	class Bezier
	{
	public:
		Bezier();
		~Bezier();

		//void calculateCurvePoints(QVector<Geometry::Point3D>& controlPointsList, QVector<double>& inCoordinates);// , QVector<double>& inColors);		
		void calculateCurvePoints(QVector<Geometry::Point3D>& controlPoints, QVector<double>& vertices);
		Geometry::Point3D calculateBezierPoint(QVector<Geometry::Point3D>& controlPoints, double t);



	};
}