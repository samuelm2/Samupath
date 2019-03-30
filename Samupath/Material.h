#pragma once
#include "Constants.h"
#include "Ray.h"
#include "glm/gtc/random.hpp"
class Material
{
public:
	RGBColor emittance;
	RGBColor reflectance;

	virtual Direction BRDF(const Ray & ray, const Direction & normal) = 0;

	Point3D get_sample3D(const Direction & normal) {
		Point3D poss = glm::sphericalRand(1.0f);
		while (glm::dot(normal, poss) < 0) {
			poss = glm::sphericalRand(1.0f);
		}
		return poss;
	};

	Material() {};
	Material(RGBColor e, RGBColor r) : emittance(e), reflectance(r) {};
	~Material();
};

