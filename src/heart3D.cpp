#include "stdafx.h"
#include "heart3D.h"
#include "bezier.h"

using namespace std;

Geometry::Heart3D::Heart3D()
{
    // Upper left part of the heart
    mControlPoints.push_back(Geometry::Point3D(0.0, 4.0, 0.0));
    mControlPoints.push_back(Geometry::Point3D(-2.0, 6.0, 0.0));
    mControlPoints.push_back(Geometry::Point3D(-4.0, 4.0, 0.0));
    mControlPoints.push_back(Geometry::Point3D(0.0, 0.0, 0.0));

    // Lower part of the heart
    mControlPoints.push_back(Geometry::Point3D(0.0, 0.0, 0.0));
    mControlPoints.push_back(Geometry::Point3D(-4.0, -6.0, 0.0));
    mControlPoints.push_back(Geometry::Point3D(0.0, -8.0, 0.0));
    mControlPoints.push_back(Geometry::Point3D(4.0, -6.0, 0.0));
    mControlPoints.push_back(Geometry::Point3D(0.0, 0.0, 0.0));

    // Upper right part of the heart
    mControlPoints.push_back(Geometry::Point3D(0.0, 0.0, 0.0));
    mControlPoints.push_back(Geometry::Point3D(4.0, 4.0, 0.0));
    mControlPoints.push_back(Geometry::Point3D(2.0, 6.0, 0.0));
    mControlPoints.push_back(Geometry::Point3D(0.0, 4.0, 0.0));
        
    
    for (int i = 0; i < mControlPoints.size(); ++i)
    {
        mColors.push_back(double(1.0));
        mColors.push_back(double(0.0));
        mColors.push_back(double(0.0));
    }

    compute();
}

Geometry::Heart3D::~Heart3D() {}

const vector<Geometry::Point3D> Geometry::Heart3D::curvePoints() const
{
    return mGeneratedPoints;
}

const vector<double> Geometry::Heart3D::curveColor() const
{
    return mColors;
}

void Geometry::Heart3D::compute()
{
    BezierCurveMath::Bezier bezier;
    bezier.calculateCurvePoints(mControlPoints, mGeneratedPoints);
}

void Geometry::Heart3D::addControlPoint(Point3D inPoint)
{
    mControlPoints.push_back(inPoint);
    mGeneratedPoints.clear();
    compute();
}
