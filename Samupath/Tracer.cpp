#include "pch.h"
#include "Tracer.h"



RGBColor Tracer::trace_ray(const Ray & r, int currentDepth)
{
	num_traced++;
	if (currentDepth == 0) { //traced enough rays
		return RGBColor(0., 0., 0.);
	}
}

long Tracer::get_num_traced()
{
	return num_traced;
}

Tracer::Tracer()
{
	num_traced = 0;
}


Tracer::~Tracer()
{
}
