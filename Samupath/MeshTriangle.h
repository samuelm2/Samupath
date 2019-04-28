#pragma once
#include "GeometricObject.h"
class MeshTriangle :
	public GeometricObject
{
public:
	Point3D p1;
	Point3D p2;
	Point3D p3;

	Point2D p1uv;
	Point2D p2uv;
	Point2D p3uv;

	Direction normal;

	bool hit(const Ray &r, double & min_t, HitInfo & hit_info) const;
	BoundingBox getBBox() const;

	MeshTriangle(const Point3D & a, const Point3D &b, const Point3D & c);
	MeshTriangle();
	~MeshTriangle();

private:
	Direction v0;
	Direction v1;

};

