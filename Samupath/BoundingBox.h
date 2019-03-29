#pragma once
class GeometricObject;
#include "GeometricObject.h"
#include <algorithm>
class BoundingBox
{
public:
	Point3D min, max;

	BoundingBox union_boxes(const BoundingBox & b2);
	BoundingBox union_boxes(const Point3D & p);
	int get_extent() const;
	bool empty;
	bool hit(const Ray & r, double & min_t, HitInfo & hit_info) const;
	bool shadow_hit(const Ray & r, double & min_t) const;
	BoundingBox getBBox() const;
	BoundingBox();
	BoundingBox(Point3D min, Point3D max);
	~BoundingBox();
};

