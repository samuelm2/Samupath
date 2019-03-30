#include "pch.h"
#include "Tracer.h"

#include "glm/gtx/norm.hpp"

RGBColor Tracer::trace_ray(const Ray & r, int currentDepth)
{
	num_traced++;
	if (currentDepth == 0) { //traced enough rays
		return zero;
	}

	HitInfo h = HitInfo();
	double min_t = MAX_DOUBLE;
	Direction new_dir = glm::normalize(r.direction);
	Ray new_ray = Ray(r);
	new_ray.direction = new_dir;
	if (bvh->hit(new_ray, min_t, h)) {
		Material* m = h.material;
		RGBColor emittance = m->emittance;
		RGBColor reflectance = m->reflectance;

		if (glm::length2(reflectance) < 0.03) {
			return emittance;
		}

		Ray next_ray = Ray();
		next_ray.origin = h.hit_point;
		next_ray.direction = m->BRDF(new_ray, h.normal);

		RGBColor incoming = trace_ray(next_ray, currentDepth - 1);

		return emittance + (reflectance * incoming);
	}
	return zero;
}

long long Tracer::get_num_traced()
{
	return num_traced;
}

Tracer::Tracer(BVHAccelerator* b)
{
	bvh = b;
	num_traced = 0;
}


Tracer::~Tracer()
{
}
