#include "pch.h"
#include "MetallicMaterial.h"


Direction MetallicMaterial::BRDF(const Ray & ray, const Direction & normal)
{
	Direction reflection = glm::reflect(ray.direction, normal);
	return reflection;
}

MetallicMaterial::MetallicMaterial()
{
}


MetallicMaterial::~MetallicMaterial()
{
}
