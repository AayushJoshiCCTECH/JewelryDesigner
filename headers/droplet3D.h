#pragma once
#include "shape3D.h"
#include "point3D.h"

using namespace std;

namespace Geometry 
{
	enum DropletCurveIndex
	{
		LeftCurve = 0,
		RightCurve,
	};

	class Droplet3D : public Shapes3D
	{
	public:
		static const QStringList CURVE_NAMES;

		Droplet3D();
		~Droplet3D();

		const vector<Geometry::Point3D> leftCurve() const;
		const vector<Geometry::Point3D> rightCurve() const;
		const vector<Geometry::Point3D> controlPoints() const;
		const vector<Geometry::Point3D> curvePoints() const;
		const vector<double> curveColor() const;
		const vector<double> offsetVertices() const;
		const vector<double> connectingVertices() const;
		const vector<double> normalVertices() const;

		void addControlPoint(Point3D inNewPoint, DropletCurveIndex inSelectedCurve);
		void updateControlPoints();
		void modifyControlPoint(Point3D inPoint, DropletCurveIndex inSelectedCurve, int inSelectedPointIndex);
		void compute();
		void generateOffsetAndConnectingVertices();
		void generateNormalVertices();

	private:
		vector<Geometry::Point3D> mLeftCurve;
		vector<Geometry::Point3D> mRightCurve;
		vector<Geometry::Point3D> mControlPoints;		
		vector<Geometry::Point3D> mGeneratedPoints;
		vector<double> mColors;
		vector<double> mOffsetVertices;
		vector<double> mConnectingVertices;
		vector<double> mNormalVertices;
		double mOffsetDistance;
	};
}