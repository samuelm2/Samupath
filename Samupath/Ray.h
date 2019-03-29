#pragma once
#include "Constants.h"
class Ray
{
public:
	Point3D origin;
	Direction direction;

	Ray(const Point3D & o, const Direction & d);
	Ray();
	~Ray();
};

