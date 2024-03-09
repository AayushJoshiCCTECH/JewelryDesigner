#pragma once
#include "shape3D.h"
#include "point3D.h"

using namespace std;

namespace Geometry
{
	class Heart3D : public Shapes3D
	{
	public:
		Heart3D();
		~Heart3D();

		const vector<Geometry::Point3D> curvePoints() const;
		const vector<double> curveColor() const;
		void addControlPoint(Point3D inPoint);

	private:
		void compute();


	private:
		vector<Geometry::Point3D> mControlPoints;
		vector<Geometry::Point3D> mGeneratedPoints;
		vector<double> mColors;
	};
}