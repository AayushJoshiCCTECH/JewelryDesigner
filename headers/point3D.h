#pragma once
namespace Geometry
{
    class Point3D
    {
    public:
        Point3D();
        Point3D(double inX, double inY, double inZ);
        ~Point3D();

        double x() const;
        double y() const;
        double z() const;

        bool operator<(const Point3D& other) const;
        Point3D& operator=(const Point3D& other);

    private:
        double mX;
        double mY;
        double mZ;
    };
}
