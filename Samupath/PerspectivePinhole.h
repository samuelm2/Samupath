#pragma once
#include "Camera.h"
#include "RenderParams.h"
class PerspectivePinhole :
	public Camera
{
public:
	void render_scene(const World * world, RawImage & raw_image, int num_threads);
	Direction calculate_ray_direction(double x, double y) const;
	
	PerspectivePinhole(Point3D o, Point3D l, Direction up, double distance);
	~PerspectivePinhole();
private:
	
	
	long long first(int id, RenderParams a);
	void run_render_threads(const World * world, RawImage & raw_image, int length, int num_threads);
};

