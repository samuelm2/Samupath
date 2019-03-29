#pragma once
#include "Constants.h"
class World;
#include "World.h"
class Camera
{
public:
	Point3D origin;
	Point3D lookat;
	Direction up;
	double vp_distance;
	void calculate_uvw();
	virtual void render_scene(const World * world, RawImage & raw_image) = 0;
	Camera(Point3D o, Point3D l, Direction up, double vp_distance);
	Camera();
	~Camera();
protected:
	Direction direction;
	Direction u;
	Direction v;
	Direction w;
};

