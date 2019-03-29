#pragma once
#include "GeometricObject.h"
#include "Constants.h"
class Sphere :
	public GeometricObject
{
public:
	bool hit(const Ray &r, double & hit_t, HitInfo & hit_info) const;
	bool shadow_hit(const Ray &r, double & min_t) const;
	BoundingBox getBBox() const;

	Sphere(const Point3D & center, double radius);
	Sphere();
	Sphere(const Sphere & rhs) = default;
	~Sphere();
	bool hit2(const Ray & r, glm::vec2 & hit_t, HitInfo & hit_info) const;

protected:
	Point3D center;
	double radius;
};

