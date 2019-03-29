#include "pch.h"
#include "RawImage.h"
#include <iostream>


void RawImage::set_pixel(int x, int y, const RGBColor & color)
{
	unsigned char char_r = (unsigned char)(color.r * 255.);
	unsigned char char_g = (unsigned char)(color.g * 255.);
	unsigned char char_b = (unsigned char)(color.b * 255.);

	y = this->view_plane.vres - y - 1; //changing because of how bmps are written to
	
	bmp.set_pixel(x, y, char_r, char_g, char_b);
	this->pixels_written++;
	
	
	//if (!(this->pixels_written % 500)) {
	//	std::cout << "Saving image iteration" << std::endl;
	//	bmp.save_image(this->name);
	//}
}

void RawImage::export_image() const
{
	bmp.save_image(this->name);
}

RawImage::RawImage(ViewPlane v, const char* name) : view_plane(v)
{
	this->pixels_written = 0;
	this->name = name;
	this->bmp = bitmap_image(v.hres, v.vres);
}

RawImage::~RawImage()
{
}

