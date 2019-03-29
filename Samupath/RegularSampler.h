#pragma once
#include "Sampler.h"
class RegularSampler :
	public Sampler
{
public:
	void generate_samples(int num_samples, int num_sets);
	RegularSampler();
	~RegularSampler();
};

