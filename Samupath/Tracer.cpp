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
		RGBColor emittance = m->get_emittance(h);

		Ray next_ray = Ray();
		next_ray.origin = h.hit_point;
		next_ray.direction = m->outgoing(new_ray, h.normal);

		RGBColor reflected_color = m->BRDF(r, next_ray, h.normal, h);

		if (glm::length2(reflected_color) < 0.03) {
			return emittance;
		}

		RGBColor incoming = trace_ray(next_ray, currentDepth - 1);

		return emittance + (reflected_color * incoming * (float)glm::dot(next_ray.direction, h.normal));
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
