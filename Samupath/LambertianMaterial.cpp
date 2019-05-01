#include "pch.h"
#include "LambertianMaterial.h"


Direction LambertianMaterial::outgoing(const Ray & ray, const Direction & normal)
{
	return get_sample3D(normal);
}

RGBColor LambertianMaterial::BRDF(const Ray & incoming, const Ray & outgoing, const Direction & normal, const HitInfo & h)
{
	return reflectance;
}

LambertianMaterial::LambertianMaterial()
{
}


LambertianMaterial::~LambertianMaterial()
{
}
