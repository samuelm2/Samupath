#pragma once
#include "Constants.h"
class Material;
#include "Material.h"
class HitInfo
{
public:
	bool did_hit;
	Point3D hit_point;
	Point2D uv;
	Direction normal;
	Material* material;

	HitInfo();
	~HitInfo();
};

