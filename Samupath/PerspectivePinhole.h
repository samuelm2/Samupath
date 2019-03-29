#pragma once
#include "Camera.h"
class PerspectivePinhole :
	public Camera
{
public:
	void render_scene(const World * world, RawImage & raw_image);
	
	PerspectivePinhole(Point3D o, Point3D l, Direction up, double distance);
	~PerspectivePinhole();
private:
	Direction calculate_ray_direction(double x, double y) const;
};

