#include "pch.h"
#include "SimpleUVMaterial.h"

Direction SimpleUVMaterial::outgoing(const Ray & ray, const Direction & normal)
{
	return get_sample3D(normal);
}

RGBColor SimpleUVMaterial::BRDF(const Ray & incoming, const Ray & outgoing, const Direction & normal, const HitInfo & h)
{
	return reflectance;
}

RGBColor SimpleUVMaterial::get_emittance(const HitInfo & h)
{
	return (float)h.uv.x * u_color + (float)h.uv.y * v_color;
}

SimpleUVMaterial::SimpleUVMaterial()
{
}


SimpleUVMaterial::~SimpleUVMaterial()
{
}
