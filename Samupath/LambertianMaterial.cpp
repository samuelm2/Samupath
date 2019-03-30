#include "pch.h"
#include "LambertianMaterial.h"


Direction LambertianMaterial::BRDF(const Ray & ray, const Direction & normal)
{
	return get_sample3D(normal);
}

LambertianMaterial::LambertianMaterial()
{
}


LambertianMaterial::~LambertianMaterial()
{
}
