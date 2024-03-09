#include "stdafx.h"
#include "heart3D.h"
#include "bezier.h"

using namespace std;

const QStringList Geometry::Heart3D::CURVE_NAMES = { "Top Left Curve", "Bottom Curve", "Top Right Curve" };

// default constructor
Geometry::Heart3D::Heart3D()
{
    // top left curve of the heart
    mTopLeftCurve.clear();
    mTopLeftCurve.push_back(Geometry::Point3D(0.0, 4.0, 0.0));
    mTopLeftCurve.push_back(Geometry::Point3D(-2.0, 6.0, 0.0));
    mTopLeftCurve.push_back(Geometry::Point3D(-4.0, 4.0, 0.0));
    mTopLeftCurve.push_back(Geometry::Point3D(0.0, 0.0, 0.0));

    // bottom curve of the heart
    mBottomCurve.clear();
    mBottomCurve.push_back(Geometry::Point3D(0.0, 0.0, 0.0));
    mBottomCurve.push_back(Geometry::Point3D(-4.0, -6.0, 0.0));
    mBottomCurve.push_back(Geometry::Point3D(0.0, -8.0, 0.0));
    mBottomCurve.push_back(Geometry::Point3D(4.0, -6.0, 0.0));
    mBottomCurve.push_back(Geometry::Point3D(0.0, 0.0, 0.0));

    // top right curve of the heart
    mTopRightCurve.clear();
    mTopRightCurve.push_back(Geometry::Point3D(0.0, 0.0, 0.0));
    mTopRightCurve.push_back(Geometry::Point3D(4.0, 4.0, 0.0));
    mTopRightCurve.push_back(Geometry::Point3D(2.0, 6.0, 0.0));
    mTopRightCurve.push_back(Geometry::Point3D(0.0, 4.0, 0.0));

    mControlPoints.clear();
    mControlPoints.insert(mControlPoints.end(), mTopLeftCurve.begin(), mTopLeftCurve.end());
    mControlPoints.insert(mControlPoints.end(), mBottomCurve.begin(), mBottomCurve.end());
    mControlPoints.insert(mControlPoints.end(), mTopRightCurve.begin(), mTopRightCurve.end());

    for (int i = 0; i < mControlPoints.size() * 100; ++i)
    {
        mColors.push_back(double(1.0));
        mColors.push_back(double(0.0));
        mColors.push_back(double(0.0));
    }
    compute();
}

Geometry::Heart3D::~Heart3D() {}

// getter functions
const vector<Geometry::Point3D> Geometry::Heart3D::topLeftCurve() const
{
    return mTopLeftCurve;
}

const vector<Geometry::Point3D> Geometry::Heart3D::bottomCurve() const
{
    return mBottomCurve;
}

const vector<Geometry::Point3D> Geometry::Heart3D::topRightCurve() const
{
    return mTopRightCurve;
}

const vector<Geometry::Point3D> Geometry::Heart3D::controlPoints() const
{
    return mControlPoints;
}

const vector<Geometry::Point3D> Geometry::Heart3D::curvePoints() const
{
    return mGeneratedPoints;
}

const vector<double> Geometry::Heart3D::curveColor() const
{
    return mColors;
}

// calculates curve points
void Geometry::Heart3D::compute()
{
    BezierCurveMath::Bezier bezier;
    bezier.calculateCurvePoints(mControlPoints, mGeneratedPoints);
}

// adds a new control point
void Geometry::Heart3D::addControlPoint(Point3D inNewPoint, string inSelectedCurve)
{
    if (inSelectedCurve == "Top Left Curve")
    {
        mTopLeftCurve.push_back(inNewPoint);
    }
    else if (inSelectedCurve == "Bottom Curve")
    {
        mTopRightCurve.push_back(inNewPoint);
    }
    else if (inSelectedCurve == "Top Right Curve")
    {
        mBottomCurve.push_back(inNewPoint);
    }    
    mGeneratedPoints.clear();
}

// updates selected point
void Geometry::Heart3D::updateControlPoints()
{
    mControlPoints.insert(mControlPoints.end(), mTopLeftCurve.begin(), mTopLeftCurve.end());
    mControlPoints.insert(mControlPoints.end(), mBottomCurve.begin(), mBottomCurve.end());
    mControlPoints.insert(mControlPoints.end(), mTopRightCurve.begin(), mTopRightCurve.end());
    compute();
}

// modifies selected point
void Geometry::Heart3D::modifyControlPoint(Point3D inPoint, string inSelectedCurve, int inSelectedPointIndex)
{
    if (inSelectedCurve == "Top Left Curve")
    {
        mTopLeftCurve[inSelectedPointIndex].setX(inPoint.x());
        mTopLeftCurve[inSelectedPointIndex].setY(inPoint.y());
        mTopLeftCurve[inSelectedPointIndex].setZ(inPoint.z());
    }
    else if (inSelectedCurve == "Bottom Curve")
    {
        mBottomCurve[inSelectedPointIndex].setX(inPoint.x());
        mBottomCurve[inSelectedPointIndex].setY(inPoint.y());
        mBottomCurve[inSelectedPointIndex].setZ(inPoint.z());

    }
    else if (inSelectedCurve == "Top Right Curve")
    {
        mTopRightCurve[inSelectedPointIndex].setX(inPoint.x());
        mTopRightCurve[inSelectedPointIndex].setY(inPoint.y());
        mTopRightCurve[inSelectedPointIndex].setZ(inPoint.z());
    }
    mGeneratedPoints.clear();
}