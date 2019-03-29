#include "pch.h"
#include "BoundingBox.h"

BoundingBox BoundingBox::union_boxes(const BoundingBox & b2)
{
	Point3D new_min = glm::min(this->min, b2.min);
	Point3D new_max = glm::max(this->max, b2.max);
	return BoundingBox(new_min, new_max);
}

BoundingBox BoundingBox::union_boxes(const Point3D & p)
{
	if (empty) {
		empty = false;
		return BoundingBox(p, p);
	}
	Point3D new_min = glm::min(this->min, p);
	Point3D new_max = glm::max(this->max, p);
	return BoundingBox(new_min, new_max);
}

int BoundingBox::get_extent() const
{
	double xdiameter = max.x - min.x;
	double ydiameter = max.y - min.y;
	double zdiameter = max.z - min.z;

	if (xdiameter >= ydiameter && xdiameter >= zdiameter) {
		return 0;
	}
	if (ydiameter >= xdiameter && ydiameter >= zdiameter) {
		return 1;
	}
	return 2;
}

//inspired from Smit's method http://www.cs.utah.edu/~awilliam/box/box.pdf
bool BoundingBox::hit(const Ray & r, double & min_t, HitInfo & hit_info) const
{
	double divx = 1./r.direction.x;
	double xnear = (min.x - r.origin.x) * divx;
	double xfar = (max.x - r.origin.x) * divx;

	if (xfar < xnear) {
		std::swap(xfar, xnear);
	}

	double divy = 1. / r.direction.y;
	double ynear = (min.y - r.origin.y) * divy;
	double yfar = (max.y - r.origin.y) * divy;

	if (yfar < ynear) {
		std::swap(yfar, ynear);
	}

	double divz = 1. / r.direction.z;
	double znear = (min.z - r.origin.z) * divz;
	double zfar = (max.z - r.origin.z) * divz;

	if (zfar < znear) {
		std::swap(zfar, znear);
	}

	if (ynear > xfar || xnear > yfar) {
		return false;
	}

	if (ynear > xnear) {
		xnear = ynear;
	}
	if (yfar < xfar) {
		xfar = yfar;
	}

	if (xnear > zfar || znear > xfar) {
		return false;
	}
	
	if (znear > xnear) {
		xnear = znear;
	}
	if (zfar < xfar) {
		xfar = zfar;
	}
	//hit_info.did_hit = true;
	//min_t = xnear;
	return xfar > 0;
}

bool BoundingBox::shadow_hit(const Ray & r, double & min_t) const
{
	return true;
}

BoundingBox BoundingBox::getBBox() const
{
	return *this;
}

BoundingBox::BoundingBox()
{
	empty = true;
}

BoundingBox::BoundingBox(Point3D min, Point3D max) : min(min), max(max)
{
	empty = false;
}


BoundingBox::~BoundingBox()
{
}
