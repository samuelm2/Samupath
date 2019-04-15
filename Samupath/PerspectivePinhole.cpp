#include "pch.h"
#include "PerspectivePinhole.h"
#include "ctpl_stl.h"
#include <sstream>
#include <vector>

long long render_chunk(int id, const RenderParams p) {
	std::stringstream msg;
	msg << "Thread " << id << " starting chunk " << p.vstart << ", " << p.hstart << "\n";
	std::cout << msg.str();
	Point3D pixel_location = Point3D();
	Point2D sample_point = Point2D();
	Ray r = Ray();
	const PerspectivePinhole* c = p.camera;
	r.origin = c->origin;
	r.direction.z = -c->origin.z;
	RGBColor curr;
	RGBColor pathCurr;

	for (int i = 0; i < p.vlength; i++) { //vertical
		for (int j = 0; j < p.hlength; j++) { //horizontal
			curr.r = 0.;
			curr.g = 0.;
			curr.b = 0.;
			int jind = (j + p.hstart);
			int iind = (i + p.vstart);
			for (int n = 0; n < p.world->view_plane.num_samples; n++) {


				pathCurr.r = 0;
				pathCurr.g = 0;
				pathCurr.b = 0;
				sample_point = p.world->view_plane.sampler->get_sample();
				pixel_location.x = p.world->view_plane.pixel_size * (jind - 0.5 * p.world->view_plane.hres + sample_point.x);
				pixel_location.y = p.world->view_plane.pixel_size * (iind - 0.5 * p.world->view_plane.vres + sample_point.y);
				r.direction = c->calculate_ray_direction(pixel_location.x, pixel_location.y);
				for (int k = 0; k < p.world->view_plane.path_samples; k++) {
					pathCurr += p.world->tracer->trace_ray(r, c->bounces);
				}
				curr += glm::clamp(pathCurr / (float)(p.world->view_plane.path_samples), zero, one);
			}
			p.raw_image->set_pixel(jind, iind, glm::clamp(curr / (float)(p.world->view_plane.num_samples), zero, one));
		}
	}
	return 0;
}

long long PerspectivePinhole::first(int id, RenderParams a) {
	std::cout << "hello from " << id << ", function\n";
	return 0;
}

void PerspectivePinhole::run_render_threads(const World* world, RawImage & raw_image, int length, int num_threads) {
	int vres = world->view_plane.vres;
	int hres = world->view_plane.hres;

	ctpl::thread_pool p(num_threads);
	RenderParams r;
	r.world = world;
	r.raw_image = &raw_image;
	r.camera = this;
	std::vector<std::future<long long>> results;
	for (int i = 0; i < vres; i += length) {
		for (int j = 0; j < hres; j += length) {
			r.hstart = i;
			r.vstart = j;
			//std::cout << i << ", " << j << "\n";
			r.vlength = std::min(vres - i, length);
			r.hlength = std::min(hres - j, length);

			std::future<long long> result = p.push(render_chunk, r);
			//results.push_back(result);
		}
	}
	bool quit = false;
	while (!quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			/* handle your event here */

		   //User requests quit
			if (event.type == SDL_QUIT)
				quit = true;
		}
		/* do some other stuff here -- draw your app, etc. */
	}
	p.stop(true);
	//long long num_rays = 0;
	//for (int i = 0; i < results.size(); i++) {
	//	num_rays += results[i].get();
	//}

	std::cout << "Number of rays traced: " << world->tracer->get_num_traced() << std::endl;
}

void PerspectivePinhole::render_scene(const World* world, RawImage & raw_image, int num_threads)
{
	if(num_threads == 1) {
		Point3D pixel_location = Point3D();
		Point2D sample_point = Point2D();
		Ray r = Ray();
		r.origin = origin;
		r.direction.z = -origin.z;
		RGBColor curr;
		RGBColor pathCurr;

		for (int i = 0; i < world->view_plane.vres; i++) {
			for (int j = 0; j < world->view_plane.hres; j++) {
				curr.r = 0.;
				curr.g = 0.;
				curr.b = 0.;
				for (int n = 0; n < world->view_plane.num_samples; n++) {
					pathCurr.r = 0;
					pathCurr.g = 0;
					pathCurr.b = 0;
					sample_point = world->view_plane.sampler->get_sample();
					pixel_location.x = world->view_plane.pixel_size * (j - 0.5 * world->view_plane.hres + sample_point.x);
					pixel_location.y = world->view_plane.pixel_size * (i - 0.5 * world->view_plane.vres + sample_point.y);
					r.direction = calculate_ray_direction(pixel_location.x, pixel_location.y);
					for (int p = 0; p < world->view_plane.path_samples; p++) {
						pathCurr += world->tracer->trace_ray(r, bounces);
					}
					curr += glm::clamp(pathCurr / (float)(world->view_plane.path_samples), zero, one);
				}
				raw_image.set_pixel(j, i, glm::clamp(curr / (float)(world->view_plane.num_samples), zero, one));

			}
		}
	}
	else {
		run_render_threads(world, raw_image, 40, num_threads);
	}
}

Direction PerspectivePinhole::calculate_ray_direction(double x, double y) const {
	Direction d = x * u + y * v - this->vp_distance*w;
	return d;
}

PerspectivePinhole::PerspectivePinhole(Point3D o, Point3D l, Direction up, double distance) : Camera(o, l, up, distance)
{
}


PerspectivePinhole::~PerspectivePinhole()
{
}
