#include "pch.h"
#include "TextureMaterial.h"


Direction TextureMaterial::BRDF(const Ray & ray, const Direction & normal)
{
	return get_sample3D(normal);
}

RGBColor TextureMaterial::get_reflectance(const HitInfo & h)
{
	return sample_texture(h.uv.x, h.uv.y);
}

TextureMaterial::TextureMaterial(std::string filename)
{
	texture = new bitmap_image(filename);
}

TextureMaterial::~TextureMaterial()
{
	delete texture;
}
