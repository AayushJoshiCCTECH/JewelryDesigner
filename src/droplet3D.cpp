#include "stdafx.h"
#include "droplet3D.h"
#include "bezier.h"

Geometry::Droplet3D::Droplet3D() 
{
    mControlPoints.push_back(Geometry::Point3D(5.0, 5.0, 5.0));
    mControlPoints.push_back(Geometry::Point3D(5.0, 5.0, 5.0));
    mControlPoints.push_back(Geometry::Point3D(10.0, 0.0, 5.0));
    mControlPoints.push_back(Geometry::Point3D(10.0, -5.0, 5.0));

    mControlPoints.push_back(Geometry::Point3D(10.0, -5.0, 5.0));
    mControlPoints.push_back(Geometry::Point3D(-5.0, 5.0, 5.0));
    mControlPoints.push_back(Geometry::Point3D(0.0, 10.0, 5.0));
    mControlPoints.push_back(Geometry::Point3D(5.0, 5.0, 5.0));

    //mBezier.calculateCurvePoints(mControlPoints, mDropletCoordinates);

    for (int i = 0; i < mControlPoints.size(); ++i)
    {
        mColors.push_back(double(0.0));
        mColors.push_back(double(0.0));
        mColors.push_back(double(1.0));
    }

    compute();
}

Geometry::Droplet3D::~Droplet3D () {}

const vector<Geometry::Point3D>& Geometry::Droplet3D::curvePoints() const
{
    return mGeneratedPoints;
}

const vector<double>& Geometry::Droplet3D::curveColor() const
{
    return mColors;
}

void Geometry::Droplet3D::compute()
{
    BezierCurveMath::Bezier bezier;
    bezier.calculateCurvePoints(mControlPoints, mGeneratedPoints);
}