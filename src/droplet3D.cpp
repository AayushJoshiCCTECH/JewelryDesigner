#include "stdafx.h"
#include "droplet3D.h"

Geometry::Droplet3D::Droplet3D() {}

Geometry::Droplet3D::~Droplet3D () {}


const QVector<Geometry::Point3D>& Geometry::Droplet3D::dropletPoints() const
{
    return mDropletPoints;
}


const QVector<double>& Geometry::Droplet3D::dropletCoordinates() const
{
    return mDropletCoordinates;
}

const QVector<double>& Geometry::Droplet3D::dropletColors() const
{
    return mDropletColors;
}

void Geometry::Droplet3D::draw()
{
    mDropletPoints.push_back(Geometry::Point3D(5.0, 5.0, 5.0));
    mDropletPoints.push_back(Geometry::Point3D(5.0, 5.0, 5.0));
    mDropletPoints.push_back(Geometry::Point3D(10.0, 0.0, 5.0));
    mDropletPoints.push_back(Geometry::Point3D(10.0, -5.0, 5.0));

    mDropletPoints.push_back(Geometry::Point3D(10.0, -5.0, 5.0));
    mDropletPoints.push_back(Geometry::Point3D(-5.0, 5.0, 5.0));
    mDropletPoints.push_back(Geometry::Point3D(0.0, 10.0, 5.0));
    mDropletPoints.push_back(Geometry::Point3D(5.0, 5.0, 5.0));

    mBezier.calculateCurvePoints(mDropletPoints, mDropletCoordinates);

    setDropletColor();	
}

void Geometry::Droplet3D::setDropletColor()
{
    
    mDropletColors.clear();

    for (int i = 0; i < mDropletCoordinates.size() / 3; ++i)
    {
        mDropletColors.push_back(0.678);
        mDropletColors.push_back(0.847);
        mDropletColors.push_back(0.902);
    }
}