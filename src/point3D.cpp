#include "stdafx.h"
#include "Point3D.h"
#include <cmath>

Geometry::Point3D::Point3D() : mX(), mY(), mZ() {}
Geometry::Point3D::Point3D(double inX, double inY, double inZ) : mX(inX), mY(inY), mZ(inZ) {}
Geometry::Point3D::~Point3D() {}

double Geometry::Point3D::x() const
{
    return mX;
}

double Geometry::Point3D::y() const
{
    return mY;
}

double Geometry::Point3D::z() const
{
    return mZ;
}

void Geometry::Point3D::setX(double inX)
{
    this->mX = inX;
}

void Geometry::Point3D::setY(double inY)
{
    this->mY = inY;
}

void Geometry::Point3D::setZ(double inZ)
{
    this->mZ = inZ;
}

bool Geometry::Point3D::operator<(const Point3D& other) const
{
    if (mX < other.mX)
        return true;
    if (mX > other.mX)
        return false;

    if (mY < other.mY)
        return true;
    if (mY > other.mY)
        return false;

    return mZ < other.mZ;
}


Geometry::Point3D& Geometry::Point3D::operator=(const Point3D& other) 
{
    if (this != &other) 
    { 
        mX = other.mX;
        mY = other.mY;
        mZ = other.mZ;
    }
    return *this;
}