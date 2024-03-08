#include "stdafx.h"
#include "heart3D.h"


Geometry::Heart3D::Heart3D() {}

Geometry::Heart3D::~Heart3D() {}

const QVector<Geometry::Point3D>& Geometry::Heart3D::heartPoints() const
{
    return mHeartPoints;
}

const QVector<double>& Geometry::Heart3D::heartCoordinates() const
{
    return mHeartCoordinates;
}

const QVector<double>& Geometry::Heart3D::heartColors() const
{
    return mHeartColors;
}

//void Geometry::Heart3D::setHeartPoints(const QVector<Geometry::Point3D>& inHeartPoints)
//{
//    mHeartPoints = inHeartPoints;
//    mHeartPoints.clear();
//    mBezier.calculateCurvePoints(mHeartPoints, mHeartCoordinates);
//}

void Geometry::Heart3D::draw()
{
    // Upper left part of the heart
    mHeartPoints.push_back(Geometry::Point3D(0.0, 4.0, 0.0));
    mHeartPoints.push_back(Geometry::Point3D(-2.0, 6.0, 0.0));
    mHeartPoints.push_back(Geometry::Point3D(-4.0, 4.0, 0.0));
    mHeartPoints.push_back(Geometry::Point3D(0.0, 0.0, 0.0));

    // Lower part of the heart
    mHeartPoints.push_back(Geometry::Point3D(0.0, 0.0, 0.0));
    mHeartPoints.push_back(Geometry::Point3D(-4.0, -6.0, 0.0));
    mHeartPoints.push_back(Geometry::Point3D(0.0, -8.0, 0.0));
    mHeartPoints.push_back(Geometry::Point3D(4.0, -6.0, 0.0));
    mHeartPoints.push_back(Geometry::Point3D(0.0, 0.0, 0.0));

    // Upper right part of the heart
    mHeartPoints.push_back(Geometry::Point3D(0.0, 0.0, 0.0));
    mHeartPoints.push_back(Geometry::Point3D(4.0, 4.0, 0.0));
    mHeartPoints.push_back(Geometry::Point3D(2.0, 6.0, 0.0));
    mHeartPoints.push_back(Geometry::Point3D(0.0, 4.0, 0.0));

    mBezier.calculateCurvePoints(mHeartPoints, mHeartCoordinates);

    setHeartColor();
}

void Geometry::Heart3D::setHeartColor()
{
    mHeartColors.clear();

    for (int i = 0; i < mHeartCoordinates.size() / 3; ++i) 
    {
        mHeartColors.push_back(1.0); 
        mHeartColors.push_back(0.0); 
        mHeartColors.push_back(0.0); 
    }
}