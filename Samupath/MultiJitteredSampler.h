#pragma once
#include "Sampler.h"
class MultiJitteredSampler :
	public Sampler
{
public:
	void generate_samples(int num_samples, int num_sets);
	void print_samples();
	MultiJitteredSampler();
private: 
	void shuffle_x();
	void shuffle_y();
};

