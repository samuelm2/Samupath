#include "pch.h"
#include "Sampler.h"
#include <random>

Point2D Sampler::get_sample()
{
	if (count % num_samples == 0) {
		jump = (rand() % num_sets) * num_samples;
	}
	return samples[(count++ + jump) % (num_samples * num_sets)];
}

Sampler::Sampler() : jump(0), count(0), samples()
{
}

Sampler::Sampler(int num_samples, int num_sets) : num_samples(num_samples), num_sets(num_sets), jump(0), count(0)
{
}


Sampler::~Sampler()
{
}
