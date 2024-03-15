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

// overload the subtraction operator
Geometry::Point3D Geometry::Point3D::operator-(const Geometry::Point3D& other) const
{
    return Geometry::Point3D(mX - other.mX, mY - other.mY, mZ - other.mZ);
}

// cross product
Geometry::Point3D Geometry::Point3D::cross(const Geometry::Point3D& other) const
{
    return Point3D
    (
        mY * other.mZ - mZ * other.mY,
        mZ * other.mX - mX * other.mZ,
        mX * other.mY - mY * other.mX
    );
}

// normalization
Geometry::Point3D Geometry::Point3D::normalize() const
{
    double length = std::sqrt(mX * mX + mY * mY + mZ * mZ);
    return Point3D(mX / length, mY / length, mZ / length);
}
