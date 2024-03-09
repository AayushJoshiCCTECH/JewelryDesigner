#pragma once
#include "shape3D.h"
#include "point3D.h"

using namespace std;

namespace Geometry
{
	class Heart3D : public Shapes3D
	{
	public:
		static const QStringList CURVE_NAMES;

		Heart3D();
		~Heart3D();

		const vector<Geometry::Point3D> topLeftCurve() const;
		const vector<Geometry::Point3D> bottomCurve() const;
		const vector<Geometry::Point3D> topRightCurve() const;
		const vector<Geometry::Point3D> controlPoints() const;
		const vector<Geometry::Point3D> curvePoints() const;
		const vector<double> curveColor() const;
		
		void addControlPoint(Point3D inNewPoint, string inSelectedCurve);
		void updateControlPoints();
		void modifyControlPoint(Point3D inPoint, string inSelectedCurve, int inSelectedPointIndex);
		void compute();
		
	private:
		vector<Geometry::Point3D> mTopLeftCurve;
		vector<Geometry::Point3D> mBottomCurve;
		vector<Geometry::Point3D> mTopRightCurve;
		vector<Geometry::Point3D> mControlPoints;
		vector<Geometry::Point3D> mGeneratedPoints;
		vector<double> mColors;
	};
}