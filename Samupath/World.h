#pragma once
#include <vector>
#include "GeometricObject.h"
#include "Sphere.h"
#include "Triangle.h"
#include "ViewPlane.h"
#include "RawImage.h"
#include "Camera.h"

class Tracer;
#include "Tracer.h"
class Camera;
#include "Camera.h"
#include "BVHAccelerator.h"
class World
{
public:
	std::vector<GeometricObject*> objects;
	RGBColor background_color;
	Camera* camera;
	Tracer* tracer;
	BVHAccelerator bvh;
	void build();
	void set_samples(int aa, int path, int bounces);
	void render_scene_perspective(RawImage & raw_image, int num_threads) const;
	void add_object(GeometricObject* obj);
	void set_resolution(int hres, int vres, double pixel_size);
	HitInfo hit_objects(const Ray &) const;
	World(const RGBColor & color);
	World();
	~World();
	ViewPlane view_plane;
};

