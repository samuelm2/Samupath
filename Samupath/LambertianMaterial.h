#pragma once
#include "Material.h"
#include "HemisphereSampler.h"
class LambertianMaterial :
	public Material
{
public:

	Direction BRDF(const Ray & ray, const Direction & normal);

	LambertianMaterial();
	~LambertianMaterial();
};

