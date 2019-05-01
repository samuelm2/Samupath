#pragma once
#include "Constants.h"
#include "Ray.h"
#include "glm/gtc/random.hpp"
class HitInfo;
#include "HitInfo.h"
class Material
{
public:
	RGBColor emittance;
	RGBColor reflectance;

	virtual RGBColor get_reflectance(const HitInfo & hit) {
		return reflectance;
	}

	virtual RGBColor get_emittance(const HitInfo & hit) {
		return emittance;
	}

	virtual Direction outgoing(const Ray & ray, const Direction & normal) = 0;

	virtual RGBColor BRDF(const Ray & incoming, const Ray & outgoing, const Direction & normal, const HitInfo & h) = 0;

	Point3D get_sample3D(const Direction & normal) {
		Point3D poss = glm::sphericalRand(1.0f);
		while (glm::dot(normal, poss) < 0) {
			poss = glm::sphericalRand(1.0f);
		}
		return poss;
	};

	Material() : emittance(), reflectance() {};
	Material(RGBColor e, RGBColor r) : emittance(e), reflectance(r) {};
	~Material();
};

