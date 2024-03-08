#pragma once

namespace Geometry
{
	class Shapes3D
	{
	public:
		Shapes3D();
		virtual ~Shapes3D();

		virtual void draw() = 0;
	};
}