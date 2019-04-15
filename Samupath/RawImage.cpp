#include "pch.h"
#include "RawImage.h"
#include <iostream>





void set_surface_pixel(SDL_Surface *surface, int x, int y, Uint32 color)
{
	Uint8 * pixel = (Uint8*)surface->pixels;
	pixel += (y * surface->pitch) + (x * sizeof(Uint32));
	*((Uint32*)pixel) = color;
}

void RawImage::set_pixel(int x, int y, const RGBColor & color)
{
	unsigned char char_r = (unsigned char)(color.r * 255.);
	unsigned char char_g = (unsigned char)(color.g * 255.);
	unsigned char char_b = (unsigned char)(color.b * 255.);

	y = this->view_plane.vres - y - 1; //changing because of how bmps are written to	
	bmp.set_pixel(x, y, char_r, char_g, char_b);

	//write to sdl window
	set_surface_pixel(surface, x, y, SDL_MapRGB(surface->format, char_r, char_g, char_b));
	SDL_UpdateWindowSurface(window);

	this->pixels_written++;
	
}

void RawImage::export_image() const
{
	bmp.save_image(this->name);
}



RawImage::RawImage(ViewPlane v, SDL_Window* window, const char* name) : view_plane(v)
{
	this->pixels_written = 0;
	this->name = name;
	this->bmp = bitmap_image(v.hres, v.vres);
	this->window = window;
	this->surface = SDL_GetWindowSurface(window);
}

RawImage::~RawImage()
{
}

