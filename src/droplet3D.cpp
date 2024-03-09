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

const vector<Geometry::Point3D> Geometry::Droplet3D::controlPoints() const
{
    return mControlPoints;
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
void Geometry::Droplet3D::addControlPoint(Point3D inNewPoint, string inSelectedCurve)
{
    if (inSelectedCurve == "Left Curve")
    {
        mLeftCurve.push_back(inNewPoint);
    }
    else if (inSelectedCurve == "Right Curve")
    {
        mLeftCurve.push_back(inNewPoint);
    }
    mGeneratedPoints.clear();
}

// updates selected point
void Geometry::Droplet3D::updateControlPoints()
{
    mControlPoints.clear();
    mControlPoints.insert(mControlPoints.end(), mLeftCurve.begin(), mLeftCurve.end());
    mControlPoints.insert(mControlPoints.end(), mRightCurve.begin(), mRightCurve.end());
    compute();
}

// modifies selected point
void Geometry::Droplet3D::modifyControlPoint(Point3D inPoint, string inSelectedCurve, int inSelectedPointIndex)
{
    if (inSelectedCurve == "Left Curve")
    {
        mLeftCurve[inSelectedPointIndex].setX(inPoint.x());
        mLeftCurve[inSelectedPointIndex].setY(inPoint.y());
        mLeftCurve[inSelectedPointIndex].setZ(inPoint.z());
    }
    else if (inSelectedCurve == "Right Curve")
    {
        mRightCurve[inSelectedPointIndex].setX(inPoint.x());
        mRightCurve[inSelectedPointIndex].setY(inPoint.y());
        mRightCurve[inSelectedPointIndex].setZ(inPoint.z());
    }
    mGeneratedPoints.clear();
}