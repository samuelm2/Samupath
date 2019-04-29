#include "pch.h"
#include "World.h"
#include "LambertianMaterial.h"
#include "MetallicMaterial.h"
#include "RefractiveMaterial.h"
#include "SimpleUVMaterial.h"
#include "TextureMaterial.h"
#include "PerspectivePinhole.h"
#include "Mesh.h"
#include "MeshTriangle.h"

//#include "MeshInstance.h"
//#include "AreaLight.h"


void World::build()
{


	this->camera = new PerspectivePinhole(Point3D(0, -50, 229.), Point3D(0., -50, 0.), Point3D(0., 1., 0.), 130);

	LambertianMaterial* lightMat = new LambertianMaterial();
	lightMat->emittance = RGBColor(20, 20, 20);
	lightMat->reflectance = zero;

	LambertianMaterial* whiteMat = new LambertianMaterial();
	whiteMat->emittance = zero;//RGBColor(.1, .1, .1);
	whiteMat->reflectance = RGBColor(.6, .6, .6);

	LambertianMaterial* redMat = new LambertianMaterial();
	redMat->emittance = zero;// RGBColor(.1, 0, 0);
	redMat->reflectance = RGBColor(.6, 0, 0);

	LambertianMaterial* greenMat = new LambertianMaterial();
	greenMat->emittance = zero;// RGBColor(0, 0., 0);
	greenMat->reflectance = RGBColor(.2, .8, .2);

	LambertianMaterial* blueMat = new LambertianMaterial();
	blueMat->emittance = zero;// RGBColor(0, 0, .1);
	blueMat->reflectance = RGBColor(0, 0, .6);

	LambertianMaterial* purpleMat = new LambertianMaterial();
	purpleMat->emittance = zero;//RGBColor(.1, .1, .1);
	purpleMat->reflectance = RGBColor(.6, 0, .6);

	MetallicMaterial* mirrorMat = new MetallicMaterial();
	mirrorMat->emittance = zero;
	mirrorMat->reflectance = RGBColor(1, 1, 1);

	RefractiveMaterial* glassMat = new RefractiveMaterial(1.5);
	glassMat->emittance = zero;
	glassMat->reflectance = RGBColor(1, 1, 1);



	//Sphere* mirror = new Sphere(Point3D(-60, 10, -30), 40);
	//mirror->material = mirrorMat;
	//objects.push_back(mirror);

	//Sphere* glass = new Sphere(Point3D(0, -60, 20), 40);
	//glass->material = glassMat;
	//objects.push_back(glass);

	//Sphere* green = new Sphere(Point3D(50, -80, -50), 40);
	//green->material = greenMat;
	//objects.push_back(green);


	Point3D bfl = Point3D(-150, -150, 250);
	Point3D bfr = Point3D(150, -150, 250);
	Point3D bbr = Point3D(150, -150, -100);
	Point3D bbl = Point3D(-150, -150, -100);

	Point3D tfl = Point3D(-150, 150, 250);
	Point3D tfr = Point3D(150, 150, 250);
	Point3D tbr = Point3D(150, 150, -100);
	Point3D tbl = Point3D(-150, 150, -100);

	Point3D lighttfl = Point3D(-50, 144, 50);
	Point3D lighttfr = Point3D(50, 144, 50);
	Point3D lighttbl = Point3D(-50, 150, -50);
	Point3D lighttbr = Point3D(50, 150, -50);

	Triangle* light1 = new Triangle(lighttfl, lighttbl, lighttbr);
	light1->material = lightMat;
	objects.push_back(light1);

	Triangle* light2 = new Triangle(lighttfr, lighttfl, lighttbr);
	light2->material = lightMat;
	objects.push_back(light2);

	Triangle* light3 = new Triangle(lighttbr, lighttbl, lighttfl);
	light3->material = lightMat;
	objects.push_back(light3);

	Triangle* light4 = new Triangle(lighttbr, lighttfl, lighttfr);
	light4->material = lightMat;
	objects.push_back(light4);

	Triangle* floor1 = new Triangle(bfl, bfr, bbr);
	floor1->material = whiteMat;
	objects.push_back(floor1);

	Triangle* floor2 = new Triangle(bfl, bbr, bbl);
	floor2->material = whiteMat;
	objects.push_back(floor2);

	Triangle* ceil1 = new Triangle(tbr, tfr, tfl);
	ceil1->material = blueMat;
	objects.push_back(ceil1);

	Triangle* ceil2 = new Triangle(tbl, tbr, tfl);
	ceil2->material = blueMat;
	objects.push_back(ceil2);

	Triangle* walll1 = new Triangle(bbl, tbl, tfl);
	walll1->material = whiteMat;
	objects.push_back(walll1);

	Triangle* walll2 = new Triangle(bbl, tfl, bfl);
	walll2->material = whiteMat;
	objects.push_back(walll2);

	Triangle* wallr1 = new Triangle(tfr, tbr, bbr);
	wallr1->material = whiteMat;
	objects.push_back(wallr1);

	Triangle* wallr2 = new Triangle(bfr, tfr, bbr);
	wallr2->material = whiteMat;
	objects.push_back(wallr2);

	Triangle* back1 = new Triangle(tbl, bbl, tbr);
	back1->material = whiteMat;
	objects.push_back(back1);

	Triangle* back2 = new Triangle(tbr, bbl, bbr);
	back2->material = whiteMat;
	objects.push_back(back2);

	Triangle* front1 = new Triangle(tfr, bfl, tfl);
	front1->material = whiteMat;
	objects.push_back(front1);

	Triangle*front2 = new Triangle(bfr, bfl, tfr);
	front2->material = whiteMat;
	objects.push_back(front2);

	TextureMaterial* t = new TextureMaterial("objects/book.bmp");
	Mesh* book = new Mesh("objects/book.obj", t, glm::vec3(0, -62, 0), -30, glm::vec3(0, 1, 0), glm::vec3(6, 6, 6), false);
	book->add_to_world(objects);

	bvh = BVHAccelerator(objects, 1);
	this->tracer = new Tracer(&bvh);




	//plane = new Plane(Point3D(0., -120., 0.), glm::normalize(Direction(0., 1., 0.)));
	//plane->is_procedural = true;
	//plane->color = RGBColor(0., 1., 0.);
}

void World::set_samples(int aa, int path, int bounces) {
	view_plane.set_samples(aa, path);
	camera->bounces = bounces;
}


void World::render_scene_perspective(RawImage & raw_image, int num_threads) const
{
	camera->render_scene(this, raw_image, num_threads);
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
	//for (int i = 0; i < objects.size(); i++) {
	//	delete this->objects[i];
	//}
	delete this->tracer;
}
