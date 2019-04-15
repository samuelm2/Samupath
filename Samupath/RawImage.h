#pragma once
#include "ViewPlane.h"
#include "glm/glm.hpp"
#include "Constants.h"
#include "bitmap_image.hpp"
#include <string>
#include <SDL.h>

class RawImage
{
public:
	ViewPlane view_plane;
	SDL_Window* window;

	const char* name;
	unsigned long pixels_written;
	void set_pixel(int x, int y, const RGBColor & color);
	void export_image() const;
	RawImage(ViewPlane v, SDL_Window* window, const char * name);
	~RawImage();
private: 
	SDL_Surface* surface;
	bitmap_image bmp;
};

