#pragma once
#include "ViewPlane.h"
#include "glm/glm.hpp"
#include "Constants.h"
#include "bitmap_image.hpp"
#include <string>

class RawImage
{
public:
	ViewPlane view_plane;
	
	const char* name;
	unsigned long pixels_written;
	void set_pixel(int x, int y, const RGBColor & color);
	void export_image() const;
	RawImage(ViewPlane v, const char* name);
	~RawImage();
private: 
	bitmap_image bmp;
};

