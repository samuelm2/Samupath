#pragma once
#include "Material.h"
class SimpleUVMaterial :
	public Material
{
public:
	RGBColor u_color;
	RGBColor v_color;
	
	Direction BRDF(const Ray & ray, const Direction & normal);

	RGBColor get_emittance(const HitInfo & h) override;

	//RGBColor get_reflectance(const HitInfo & h) override;

	SimpleUVMaterial();
	~SimpleUVMaterial();
};

