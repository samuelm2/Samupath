#include "pch.h"
#include "BVHObjectInfo.h"


BVHObjectInfo::BVHObjectInfo(int id, const BoundingBox & bbox) : id(id), bbox(bbox)
{
	center = .5 * bbox.min + .5 * bbox.max;
}

BVHObjectInfo::~BVHObjectInfo()
{
}
