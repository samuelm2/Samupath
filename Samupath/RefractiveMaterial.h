#pragma once
#include "Material.h"
class RefractiveMaterial :
	public Material
{
public:

	double refractive_index;

	Direction outgoing(const Ray & ray, const Direction & normal);
	RGBColor BRDF(const Ray & incoming, const Ray & outgoing, const Direction & normal, const HitInfo & h);


	RefractiveMaterial() : Material() {};
	RefractiveMaterial(float r) : Material(), refractive_index(r) {};
	~RefractiveMaterial();

private:
	Direction refract(const Direction &I, const Direction &N, const double &ior);
	void fresnel(const Direction &I, const Direction &N, const double &ior, double &kr);
};

