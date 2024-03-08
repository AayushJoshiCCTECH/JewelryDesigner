#pragma once
#include "shape3D.h"
#include "bezier.h"

namespace Geometry
{
	class Heart3D : public Shapes3D
	{
	public:
		Heart3D();
		~Heart3D();

		const QVector<Geometry::Point3D>& heartPoints() const;
		const QVector<double>& heartCoordinates() const;
		const QVector<double>& heartColors() const;

		//void setHeartPoints(const QVector<Geometry::Point3D>& inHeartPoints);
		void setHeartColor();
		void draw() override;

	private:
		QVector<Geometry::Point3D> mHeartPoints;
		QVector<double> mHeartCoordinates;
		QVector<double> mHeartColors;

		BezierCurveMath::Bezier mBezier;
	};
}