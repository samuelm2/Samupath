#pragma once
#include "Constants.h"
#include "Ray.h"
class Tracer
{
public:
	RGBColor trace_ray(const Ray & r, int currentDepth);
	long get_num_traced();

	Tracer();
	~Tracer();

private: 
	long num_traced;

};

