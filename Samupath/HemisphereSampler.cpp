#include "pch.h"
#include "HemisphereSampler.h"


Point2D HemisphereSampler::get_sample()
{
	return glm::diskRand(1.0f);
}



HemisphereSampler::HemisphereSampler()
{
}


HemisphereSampler::~HemisphereSampler()
{
}
