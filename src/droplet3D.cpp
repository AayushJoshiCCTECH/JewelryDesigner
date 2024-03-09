#include "stdafx.h"
#include "droplet3D.h"
#include "bezier.h"

const QStringList Geometry::Droplet3D::CURVE_NAMES = { "Left Curve", "Right Curve" };


// default constructor
Geometry::Droplet3D::Droplet3D() 
{
    mLeftCurve.clear();
    mLeftCurve.push_back(Geometry::Point3D(10.0, -5.0, 5.0));
    mLeftCurve.push_back(Geometry::Point3D(-5.0, 5.0, 5.0));
    mLeftCurve.push_back(Geometry::Point3D(0.0, 10.0, 5.0));
    mLeftCurve.push_back(Geometry::Point3D(5.0, 5.0, 5.0));

    mRightCurve.clear();
    mRightCurve.push_back(Geometry::Point3D(5.0, 5.0, 5.0));
    mRightCurve.push_back(Geometry::Point3D(5.0, 5.0, 5.0));
    mRightCurve.push_back(Geometry::Point3D(10.0, 0.0, 5.0));
    mRightCurve.push_back(Geometry::Point3D(10.0, -5.0, 5.0));

    mControlPoints.clear();
    mControlPoints.insert(mControlPoints.end(), mLeftCurve.begin(), mLeftCurve.end());
    mControlPoints.insert(mControlPoints.end(), mRightCurve.begin(), mRightCurve.end());

    for (int i = 0; i < mControlPoints.size() * 100; ++i)
    {
        mColors.push_back(double(0.0));
        mColors.push_back(double(0.0));
        mColors.push_back(double(1.0));
    }
    compute();
}

Geometry::Droplet3D::~Droplet3D () {}

// getter functions
const vector<Geometry::Point3D> Geometry::Droplet3D::leftCurve() const
{
    return mLeftCurve;
}

const vector<Geometry::Point3D> Geometry::Droplet3D::rightCurve() const
{
    return mRightCurve;
}

const vector<Geometry::Point3D> Geometry::Droplet3D::curvePoints() const
{
    return mGeneratedPoints;
}

const vector<double> Geometry::Droplet3D::curveColor() const
{
    return mColors;
}

// calculates curve points
void Geometry::Droplet3D::compute()
{
    BezierCurveMath::Bezier bezier;
    bezier.calculateCurvePoints(mControlPoints, mGeneratedPoints);
}

// adds a new control point
void Geometry::Droplet3D::addControlPoint(Point3D inPoint)
{
    mControlPoints.push_back(inPoint);
    mGeneratedPoints.clear();
    compute();
}
