#pragma once
#include "Constants.h"
#include <vector>
class Sampler
{
public:
	Point2D get_sample();
	virtual void generate_samples(int num_samples, int num_sets) = 0;
	Sampler();
	Sampler(int num_samples, int num_sets);
	~Sampler();

protected:
	std::vector<Point2D> samples;
	uint32_t count;
	uint32_t num_samples;
	uint32_t num_sets;
	int jump;
};

