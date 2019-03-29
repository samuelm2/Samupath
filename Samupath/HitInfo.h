#pragma once
#include "Constants.h"
#include "Material.h"
class HitInfo
{
public:
	bool did_hit;
	Point3D hit_point;
	Direction normal;
	Material* material;

	HitInfo();
	~HitInfo();
};

