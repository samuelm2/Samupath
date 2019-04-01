#pragma once
#include "Material.h"
class RefractiveMaterial :
	public Material
{
public:

	double refractive_index;

	Direction BRDF(const Ray & ray, const Direction & normal);


	RefractiveMaterial() : Material() {};
	RefractiveMaterial(float r) : Material(), refractive_index(r) {};
	~RefractiveMaterial();

private:
	Direction refract(const Direction &I, const Direction &N, const double &ior);
	void fresnel(const Direction &I, const Direction &N, const double &ior, double &kr);
};

