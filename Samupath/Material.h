#pragma once
#include "Constants.h"
#include "Ray.h"
class Material
{
public:
	RGBColor emittance;
	RGBColor reflectance;

	virtual void BRDF(const Ray & ray, int depth) = 0;

	Material() {};
	~Material();
};

