#include "stdafx.h"
#include "droplet3D.h"
#include "bezier.h"

const QStringList Geometry::Droplet3D::CURVE_NAMES = { "Left Curve", "Right Curve" };

// default constructor
Geometry::Droplet3D::Droplet3D() 
{
    mLeftCurve.clear();   
    mLeftCurve.push_back(Geometry::Point3D(0.0, 0.0, 0.0));
    mLeftCurve.push_back(Geometry::Point3D(5.0, -4.0, 0.0));
    mLeftCurve.push_back(Geometry::Point3D(4.0, -8.0, 0.0));
    mLeftCurve.push_back(Geometry::Point3D(0.0, -12.0, 0.0));
    mRightCurve.push_back(Geometry::Point3D(0.0, 0.0, 0.0));
  
    mRightCurve.clear();
    mRightCurve.push_back(Geometry::Point3D(0.0, -12.0, 0.0));
    mRightCurve.push_back(Geometry::Point3D(-4.0, -8.0, 0.0));
    mRightCurve.push_back(Geometry::Point3D(-5.0, -4.0, 0.0));
    mRightCurve.push_back(Geometry::Point3D(0.0, 0.0, 0.0));

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

    mOffsetDistance = 5.0;
}

Geometry::Droplet3D::~Droplet3D () 
{

}

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

const vector<double> Geometry::Droplet3D::offsetVertices() const
{
    return mOffsetVertices;
}

const vector<double> Geometry::Droplet3D::connectingVertices() const
{
    return mConnectingVertices;
}

const vector<double> Geometry::Droplet3D::normalVertices() const
{
    return mNormalVertices;
}

// calculates curve points
void Geometry::Droplet3D::compute()
{
    BezierCurveMath::Bezier bezier;
    bezier.calculateCurvePoints(mControlPoints, mGeneratedPoints);   
    generateNormalVertices();
}

// adds a new control point
void Geometry::Droplet3D::addControlPoint(Point3D inNewPoint, DropletCurveIndex inSelectedCurve)
{
    switch (inSelectedCurve)
    {
    case LeftCurve:
        mLeftCurve.push_back(inNewPoint);
        break;
        
    case RightCurve:
        mRightCurve.push_back(inNewPoint);
        break;
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
void Geometry::Droplet3D::modifyControlPoint(Point3D inPoint, DropletCurveIndex inSelectedCurve, int inSelectedPointIndex)
{
    vector<Point3D>* selectedCurve = nullptr;

    switch (inSelectedCurve)
    {
    case LeftCurve:
        selectedCurve = &mLeftCurve;
        break;
    
    case RightCurve:
        selectedCurve = &mRightCurve;
        break;
    }

    if (selectedCurve && inSelectedPointIndex >= 0 && inSelectedPointIndex < selectedCurve->size())
    {
        (*selectedCurve)[inSelectedPointIndex] = inPoint;
        mGeneratedPoints.clear();
    }
}

// generates offset and connecting vertices
void Geometry::Droplet3D::generateOffsetAndConnectingVertices()
{
    mOffsetVertices.clear();
    mConnectingVertices.clear();

    // generate offset vertices
    for (const auto& point : mGeneratedPoints)
    {
        mOffsetVertices.push_back(point.x());
        mOffsetVertices.push_back(point.y());
        mOffsetVertices.push_back(point.z() + mOffsetDistance);
    }

    // generate connecting vertices
    for (size_t i = 0; i < mGeneratedPoints.size(); ++i)
    {
        // first point of triangle (original curve)
        mConnectingVertices.push_back(mGeneratedPoints[i].x());
        mConnectingVertices.push_back(mGeneratedPoints[i].y());
        mConnectingVertices.push_back(mGeneratedPoints[i].z());

        // second point of triangle (extruded curve)
        mConnectingVertices.push_back(mOffsetVertices[3 * i]);
        mConnectingVertices.push_back(mOffsetVertices[3 * i + 1]);
        mConnectingVertices.push_back(mOffsetVertices[3 * i + 2]);
    }

    if (!mGeneratedPoints.empty())
    {
        // Repeat the first point of the original curve
        mConnectingVertices.push_back(mGeneratedPoints[0].x());
        mConnectingVertices.push_back(mGeneratedPoints[0].y());
        mConnectingVertices.push_back(mGeneratedPoints[0].z());

        // Repeat the first point of the offset curve
        mConnectingVertices.push_back(mOffsetVertices[0]);
        mConnectingVertices.push_back(mOffsetVertices[1]);
        mConnectingVertices.push_back(mOffsetVertices[2]);
    }
}

// generates normal vertices

// generates normal vertices
void Geometry::Droplet3D::generateNormalVertices()
{
    mNormalVertices.clear();

    if (mGeneratedPoints.size() < 3)
    {
        return;
    }

    for (size_t i = 0; i < mGeneratedPoints.size(); ++i)
    {
        Point3D point1 = mGeneratedPoints[i];
        Point3D point2 = mGeneratedPoints[(i + 1) % mGeneratedPoints.size()];
        Point3D point3 = mGeneratedPoints[(i + 2) % mGeneratedPoints.size()];

        // calculate vectors for two edges sharing the vertex
        Point3D edge1 = point2 - point1;
        Point3D edge2 = point3 - point2;

        // calculate normal using cross product of the two edge vectors
        Point3D normal = edge1.cross(edge2);
        normal.normalize(); // Ensure the normal is a unit vector

        // add normal list of normal vertices
        mNormalVertices.push_back(normal.x());
        mNormalVertices.push_back(normal.y());
        mNormalVertices.push_back(normal.z());
    }
}
