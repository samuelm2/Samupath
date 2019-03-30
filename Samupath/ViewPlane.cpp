#include "pch.h"
#include "ViewPlane.h"
#include "MultiJitteredSampler.h"
#include "RegularSampler.h"

ViewPlane::ViewPlane()
{
	this->hres = 8;
	this->vres = 6;
	this->pixel_size = 1.;
}

void ViewPlane::set_samples(int aa, int p) {
	path_samples = p;
	num_samples = aa;
	if (aa == 1) {
		this->sampler = new RegularSampler();
		this->sampler->generate_samples(aa, 87);
		return;
	}
	this->sampler = new MultiJitteredSampler();
	this->sampler->generate_samples(aa, 87);
}

ViewPlane::ViewPlane(int hres, int vres, double pixel_size) : hres(hres), vres(vres), pixel_size(pixel_size)
{
}

ViewPlane::~ViewPlane()
{
}
