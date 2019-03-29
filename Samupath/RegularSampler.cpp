#include "pch.h"
#include "RegularSampler.h"


void RegularSampler::generate_samples(int num_samples, int num_sets)
{
	this->num_samples = num_samples;
	this->num_sets = num_sets;
	Point2D p = Point2D(.5, .5);
	for (int i = 0; i < num_samples*num_sets; i++) {
		samples.push_back(p);
	}
}

RegularSampler::RegularSampler()
{
}


RegularSampler::~RegularSampler()
{
}
