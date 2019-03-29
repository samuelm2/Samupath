#pragma once
#include "Sampler.h"
class ViewPlane
{
public:
	int hres;
	int vres;
	double pixel_size;
	Sampler* sampler;
	int num_samples;

	ViewPlane();
	void set_samples(int s);
	ViewPlane(int hres, int vres, double pixel_size);
	~ViewPlane();
};

