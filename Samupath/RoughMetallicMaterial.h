#pragma once
#include "Material.h"
class RoughMetallicMaterial :
	public Material
{
public:
	Direction outgoing(const Ray & ray, const Direction & normal);
	RGBColor BRDF(const Ray & incoming, const Ray & outgoing, const Direction & normal, const HitInfo & h);

	double roughness;

	RoughMetallicMaterial();
	~RoughMetallicMaterial();
};

