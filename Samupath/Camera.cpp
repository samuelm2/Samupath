#include "pch.h"
#include "Camera.h"


void Camera::calculate_uvw()
{
	w = glm::normalize(origin - lookat);
	u = glm::normalize(glm::cross(up, w));
	v = glm::cross(w, u);
}

Camera::Camera() : origin(0., 0., 200.), vp_distance(200.), up(0., 1., 0.), lookat(0., 0., -1.)
{
	direction = glm::normalize(lookat - origin);
	calculate_uvw();
}

Camera::Camera(Point3D o, Point3D l, Direction up, double vp_distance) : origin(o), lookat(l), up(up), vp_distance(vp_distance)
{
	direction = glm::normalize(l - o);
	calculate_uvw();
}


Camera::~Camera()
{
}
