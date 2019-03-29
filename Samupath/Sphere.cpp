#include "pch.h"
#include "Sphere.h"

Sphere::Sphere(const Point3D & center, double radius) {
	this->center = Point3D(center);
	this->radius = radius;

}

Sphere::Sphere() : Sphere(Point3D(0., 0., 0.), 0.)
{

}


Sphere::~Sphere()
{
}

bool Sphere::hit2(const Ray &r, glm::vec2 & hit_t , HitInfo & hit_info) const {
	//Direction o_minus_c = r.origin - this->center;
	//double a = glm::dot(r.direction, r.direction);
	//double b = glm::dot((2. * (o_minus_c)), r.direction);
	//double c = glm::dot(o_minus_c, o_minus_c) - (this->radius * this->radius);

	//double disc = b * b - 4 * a*c;
	//bool found = false;

	//if (disc < 0.) {
	//	return false;
	//}
	//else {
	//	double sqrt_disc = glm::sqrt(disc);
	//	double t = (-b - sqrt_disc) / (2 * a);

	//	
	//	if (t > TINY_DOUBLE) {
	//		Point3D hit_point = r.origin + t * r.direction;
	//		hit_info.normal = glm::normalize(hit_point - center);
	//		hit_info.hit_point = hit_point;
	//		hit_info.color = this->color;
	//		hit_info.did_hit = true;
	//		hit_t[0] = t;
	//		hit_info.is_light = is_light;
	//		hit_info.is_reflective = is_reflective;
	//		hit_info.is_transparent = is_transparent;
	//		hit_info.is_procedural = is_procedural;
	//		hit_info.is_noise = is_noise;
	//		found = true;
	//	}
	//	t = (-b + sqrt_disc) / (2 * a);
	//	if (t > TINY_DOUBLE) {
	//		Point3D hit_point = r.origin + t * r.direction;
	//		hit_t[1] = t;
	//		hit_info.normal2 = glm::normalize(hit_point - center);
	//		if (!found) {
	//			hit_info.normal = glm::normalize(hit_point - center);
	//			hit_info.hit_point = hit_point;
	//			hit_info.color = this->color;
	//			hit_info.did_hit = true;
	//			hit_info.is_light = is_light;
	//			hit_info.is_reflective = is_reflective;
	//			hit_info.is_transparent = is_transparent;
	//			hit_info.is_procedural = is_procedural;
	//			hit_info.is_noise = is_noise;

	//			found = true;
	//		}
	//	}
	//}
	//return found;
	return false;
}

bool Sphere::hit(const Ray &r, double & hit_t, HitInfo & hit_info) const {
	Direction o_minus_c = r.origin - this->center;
	double a = glm::dot(r.direction, r.direction);
	double b = glm::dot((2. * (o_minus_c)), r.direction);
	double c = glm::dot(o_minus_c, o_minus_c) - (this->radius * this->radius);

	double disc = b * b - 4 * a*c;

	if (disc < 0.) {
		return false;
	}
	else {
		double sqrt_disc = glm::sqrt(disc);
		double t = (-b - sqrt_disc) / (2 * a);
		if (t > TINY_DOUBLE) {
			Point3D hit_point = r.origin + t * r.direction;
			hit_info.normal = glm::normalize(hit_point - center);
			hit_info.hit_point = hit_point;
			hit_info.material = this->material;
			hit_info.did_hit = true;
			hit_t = t;

			return true;
		}
		t = (-b + sqrt_disc) / (2 * a);
		if (t > TINY_DOUBLE) {
			Point3D hit_point = r.origin + t * r.direction;
			hit_info.normal = glm::normalize(hit_point - center);
			hit_info.hit_point = hit_point;
			hit_info.material = this->material;
			hit_info.did_hit = true;
			hit_t = t;


			return true;
		}
	}
	return false;
}

bool Sphere::shadow_hit(const Ray & r, double & min_t) const
{
	Direction o_minus_c = r.origin - this->center;
	double a = glm::dot(r.direction, r.direction);
	double b = glm::dot((2. * (o_minus_c)), r.direction);
	double c = glm::dot(o_minus_c, o_minus_c) - (this->radius * this->radius);

	double disc = b * b - 4 * a*c;

	if (disc < 0.) {
		return false;
	}
	else {
		double sqrt_disc = glm::sqrt(disc);
		double t = (-b - sqrt_disc) / (2 * a);
		if (t > TINY_DOUBLE && t < min_t) {

			return true;
		}
		t = (-b + sqrt_disc) / (2 * a);
		if (t > TINY_DOUBLE && t < min_t) {
			return true;
		}
	}
	return false;
}

BoundingBox Sphere::getBBox() const
{
	return BoundingBox(center - radius, center + radius);
}
