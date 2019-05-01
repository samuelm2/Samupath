#pragma once
#include "Material.h"
#include "bitmap_image.hpp"
class TextureMaterial :
	public Material
{
public:
	Direction outgoing(const Ray & ray, const Direction & normal);
	RGBColor BRDF(const Ray & incoming, const Ray & outgoing, const Direction & normal, const HitInfo & h);

	RGBColor get_reflectance(const HitInfo & h) override;
	bitmap_image* texture;
	TextureMaterial(std::string filename);
	~TextureMaterial();

private:
	inline RGBColor sample_texture(float u, float v) {
		unsigned char r, g, b;

		unsigned int x, y;
		x = (unsigned int)(u * (double)texture->width());
		y = (unsigned int)(v * (double)texture->height());

		texture->get_pixel(x, texture->height() - 1 - y, r, g, b);

		return RGBColor(r / 255., g / 255., b / 255.);
	}
};

