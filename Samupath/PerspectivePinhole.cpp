#include "pch.h"
#include "PerspectivePinhole.h"


void PerspectivePinhole::render_scene(const World* world, RawImage & raw_image)
{
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
					pathCurr += world->tracer->trace_ray(r, 12);
				}
				curr += glm::clamp(pathCurr/ (float)(world->view_plane.path_samples), zero, one);
			}
			raw_image.set_pixel(j, i, glm::clamp(curr/(float)(world->view_plane.num_samples), zero, one));
			//raw_image.set_pixel(j, i, glm::clamp(curr, zero, one));

		}
	}
	std::cout << "Number of rays traced: " << world->tracer->get_num_traced() << std::endl;
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
