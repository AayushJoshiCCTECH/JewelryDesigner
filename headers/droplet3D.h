#pragma once
#include "shape3D.h"
#include "bezier.h"

namespace Geometry 
{
	class Droplet3D : public Shapes3D
	{
	public:
		Droplet3D();
		~Droplet3D();


		const QVector<Geometry::Point3D>& dropletPoints() const;
		const QVector<double>& dropletCoordinates() const;
		const QVector<double>& dropletColors() const;

		void setDropletColor();
		void draw() override;

	private:
		QVector<Geometry::Point3D> mDropletPoints;
		QVector<double> mDropletCoordinates;
		QVector<double> mDropletColors;

		BezierCurveMath::Bezier mBezier;
	};
}