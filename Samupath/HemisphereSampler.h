#pragma once
#include "Sampler.h"
#include "glm/gtc/random.hpp"
class HemisphereSampler :
	public Sampler
{
public:
	Point2D get_sample();
	void generate_samples(int num_samples, int num_sets) {};
	HemisphereSampler();
	~HemisphereSampler();
};



