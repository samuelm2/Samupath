#pragma once
#include "Material.h"
class MetallicMaterial :
	public Material
{
public:
	Direction BRDF(const Ray & ray, const Direction & normal);

	MetallicMaterial();
	~MetallicMaterial();
};

