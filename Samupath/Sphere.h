#pragma once
#include "GeometricObject.h"
#include "Constants.h"
class Sphere :
	public GeometricObject
{
public:
	bool hit(const Ray &r, double & hit_t, HitInfo & hit_info) const;
	BoundingBox getBBox() const;

	Sphere(const Point3D & center, double radius);
	Sphere();
	Sphere(const Sphere & rhs) = default;
	~Sphere();

protected:
	Point3D center;
	double radius;
};

