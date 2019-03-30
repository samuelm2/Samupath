#pragma once
#include "Constants.h"
#include "Ray.h"
#include "HitInfo.h"
#include "BVHAccelerator.h"
class Tracer
{
public:
	RGBColor trace_ray(const Ray & r, int currentDepth);
	long long get_num_traced();

	Tracer(BVHAccelerator* b);
	~Tracer();

private: 
	long long num_traced;
	BVHAccelerator* bvh;

};

