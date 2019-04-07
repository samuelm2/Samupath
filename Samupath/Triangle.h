#pragma once
#include "GeometricObject.h"
class Triangle :
	public GeometricObject
{
public:
	Point3D p1;
	Point3D p2;
	Point3D p3;
	Direction normal;

	bool hit(const Ray &r, double & min_t, HitInfo & hit_info) const;
	BoundingBox getBBox() const;

	Triangle(const Point3D & a, const Point3D &b, const Point3D & c);
	Triangle();
	~Triangle();
};

