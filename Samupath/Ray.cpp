#include "pch.h"
#include "Ray.h"

Ray::Ray(const Point3D & o, const Direction & d) {
	this->origin = Point3D(o);
	this->direction = Direction(d);
}

Ray::Ray()
{
	this->origin = glm::vec3();
	this->direction = glm::vec3();
}

Ray::~Ray()
{
}
