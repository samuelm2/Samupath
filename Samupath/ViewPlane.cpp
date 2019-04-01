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

void ViewPlane::set_samples(int aa_samples, int path_samples) {
	this->path_samples = path_samples;
	num_samples = aa_samples;
	if (aa_samples == 1) {
		this->sampler = new RegularSampler();
		this->sampler->generate_samples(aa_samples, 87);
		return;
	}
	this->sampler = new MultiJitteredSampler();
	this->sampler->generate_samples(aa_samples, 87);
}

ViewPlane::ViewPlane(int hres, int vres, double pixel_size) : hres(hres), vres(vres), pixel_size(pixel_size)
{
}

ViewPlane::~ViewPlane()
{
}
