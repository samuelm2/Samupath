#include "pch.h"
#include "RoughMetallicMaterial.h"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtc/random.hpp"
#include "glm/gtx/perpendicular.hpp"


Direction RoughMetallicMaterial::outgoing(const Ray & ray, const Direction & normal)
{
	Direction microfacet_normal = normal;
	double random_angle = glm::clamp(glm::gaussRand(0., roughness * 25), -90., 90.);
	microfacet_normal = glm::rotate(microfacet_normal, random_angle, glm::perp(glm::sphericalRand<double>(1.), microfacet_normal));
	auto actual_reflection = glm::reflect(ray.direction, normal);
	auto reflection = glm::reflect(ray.direction, microfacet_normal);
	return reflection;
}

RGBColor RoughMetallicMaterial::BRDF(const Ray & incoming, const Ray & outgoing, const Direction & normal, const HitInfo & h)
{
	return reflectance;
}

RoughMetallicMaterial::RoughMetallicMaterial()
{
}


RoughMetallicMaterial::~RoughMetallicMaterial()
{
}
