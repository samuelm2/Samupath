#include "pch.h"
#include "MetallicMaterial.h"


Direction MetallicMaterial::outgoing(const Ray & ray, const Direction & normal)
{
	Direction reflection = glm::reflect(ray.direction, normal);
	return reflection;
}

RGBColor MetallicMaterial::BRDF(const Ray & incoming, const Ray & outgoing, const Direction & normal, const HitInfo & h)
{
	return reflectance;
}

MetallicMaterial::MetallicMaterial()
{
}


MetallicMaterial::~MetallicMaterial()
{
}
