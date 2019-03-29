#include "pch.h"
#include "World.h"
#include "PerspectivePinhole.h"

//#include "Mesh.h"
//#include "MeshInstance.h"
//#include "AreaLight.h"


void World::build()
{

	view_plane.set_samples(64);
	this->camera = new PerspectivePinhole(Point3D(-100, 46, 200.), Point3D(0., 46., 0.), Point3D(0., 1., 0.), 200) ;

	bvh = BVHAccelerator(objects, 1);

	//plane = new Plane(Point3D(0., -120., 0.), glm::normalize(Direction(0., 1., 0.)));
	//plane->is_procedural = true;
	//plane->color = RGBColor(0., 1., 0.);
}


void World::render_scene_perspective(RawImage & raw_image) const
{
	camera->render_scene(this, raw_image);
}

void World::add_object(GeometricObject * obj)
{
	objects.push_back(obj);
}

//void World::add_light(Light * light)
//{
//	lights.push_back(light);
//}

void World::set_resolution(int hres, int vres, double pixel_size)
{
	this->view_plane.hres = hres;
	this->view_plane.vres = vres;
	this->view_plane.pixel_size = pixel_size;
}

HitInfo World::hit_objects(const Ray & ray) const
{
	HitInfo h = HitInfo();
	double min_t = MAX_DOUBLE;
	Direction new_dir = glm::normalize(ray.direction);
	Ray new_ray = Ray(ray);
	new_ray.direction = new_dir;
	bvh.hit(new_ray, min_t, h);

	return h;
	//HitInfo plane_h = HitInfo();
	//double plane_min_t = MAX_DOUBLE;
	//if (plane) {
	//	plane->hit(new_ray, plane_min_t, plane_h);
	//}


	//if (plane_h.did_hit) {
	//	return (min_t < plane_min_t) ? h : plane_h;
	//}
	//else return h;
}

World::World(const RGBColor & color)
{
	this->objects = std::vector<GeometricObject*>();
	this->background_color = RGBColor(color);
	this->view_plane =  ViewPlane();
}

World::World() : background_color(0., 0., 0.)
{
	this->objects = std::vector<GeometricObject*>();
	this->view_plane =  ViewPlane();
}


World::~World()
{
	for (int i = 0; i < objects.size(); i++) {
		delete this->objects[i];
	}
	delete this->tracer;
}
