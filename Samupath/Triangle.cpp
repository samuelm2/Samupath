#include "pch.h"
#include "Triangle.h"
#include <algorithm>



bool Triangle::hit(const Ray &r, double & min_t, HitInfo & hit_info) const {
	double a = p1.x - p2.x;
	double b = p1.x - p3.x;
	double c = r.direction.x;
	double d = p1.x - r.origin.x;
	double e = p1.y - p2.y;
	double f = p1.y - p3.y;
	double g = r.direction.y;
	double h = p1.y - r.origin.y;
	double i = p1.z - p2.z;
	double j = p1.z - p3.z;
	double k = r.direction.z;
	double l = p1.z - r.origin.z;

	double denom = 1. / (a * (f * k - g * j) + b * (g * i - e * k) + c * (e * j - f * i));

	double beta = (d * (f * k - g * j) + b * (g * l - h * k) + c * (h * j - f * l)) * denom;

	if (beta < 0.) {
		return false;
	}

	double gamma = (a * (h * k - g * l) + d * (g * i - e * k) + c * (e * l - h * i)) * denom;
	if (gamma < 0.) {
		return false;
	}

	if (gamma + beta > 1.) {
		return false;
	}

	double t = (a * (f * l - h * j) + b * (h * i - e * l) + d * (e * j - f * i)) * denom;
	if (t < TINY_DOUBLE) {
		return false;
	}

	hit_info.material = this->material;
	hit_info.normal = this->normal;
	hit_info.did_hit = true;
	min_t = t;
	return true;
}

bool Triangle::shadow_hit(const Ray & r, double & min_t) const
{
	double a = p1.x - p2.x;
	double b = p1.x - p3.x;
	double c = r.direction.x;
	double d = p1.x - r.origin.x;
	double e = p1.y - p2.y;
	double f = p1.y - p3.y;
	double g = r.direction.y;
	double h = p1.y - r.origin.y;
	double i = p1.z - p2.z;
	double j = p1.z - p3.z;
	double k = r.direction.z;
	double l = p1.z - r.origin.z;

	double denom = 1. / (a * (f * k - g * j) + b * (g * i - e * k) + c * (e * j - f * i));

	double beta = (d * (f * k - g * j) + b * (g * l - h * k) + c * (h * j - f * l)) * denom;

	if (beta < 0.) {
		return false;
	}

	double gamma = (a * (h * k - g * l) + d * (g * i - e * k) + c * (e * l - h * i)) * denom;
	if (gamma < 0.) {
		return false;
	}

	if (gamma + beta > 1.) {
		return false;
	}

	double t = (a * (f * l - h * j) + b * (h * i - e * l) + d * (e * j - f * i)) * denom;
	if (t < TINY_DOUBLE || t > min_t) {
		return false;
	}
	return true;
}

BoundingBox Triangle::getBBox() const
{
	double minx = std::min(p1.x, std::min(p2.x, p3.x));
	double miny = std::min(p1.y, std::min(p2.y, p3.y));
	double minz = std::min(p1.z, std::min(p2.z, p3.z));

	double maxx = std::max(p1.x, std::max(p2.x, p3.x));
	double maxy = std::max(p1.y, std::max(p2.y, p3.y));
	double maxz = std::max(p1.z, std::max(p2.z, p3.z));


	return BoundingBox(Point3D(minx, miny, minz), Point3D(maxx, maxy, maxz));
}

Triangle::Triangle(const Point3D & a, const Point3D & b, const Point3D & c) : p1(a), p2(b), p3(c)
{
	Direction ab = b - a;
	Direction ac = c - a;
	this->normal = glm::normalize(glm::cross(ab, ac));
}

Triangle::Triangle()
{
	this->p1 = Point3D(0., 0., 0.);
	this->p2 = Point3D(0., 0., 0.);
	this->p3 = Point3D(0., 0., 0.);
	this->normal = Direction(0., 0., 0.);
}


Triangle::~Triangle()
{
}
