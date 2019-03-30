#pragma once
#include "Ray.h"
#include "HitInfo.h"
class BoundingBox;
#include "BoundingBox.h"

#include "Material.h"
class GeometricObject
{
public:
	Material* material;


	virtual BoundingBox getBBox() const = 0;
	virtual bool hit(const Ray &r, double & min_t, HitInfo & hit_info) const = 0;
	//virtual bool shadowHit(const Ray &r, double & min_t) const = 0;
	GeometricObject();
	GeometricObject(const RGBColor & color);
	~GeometricObject();

};

