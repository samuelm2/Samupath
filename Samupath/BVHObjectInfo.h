#pragma once
#include "Constants.h"
#include "BoundingBox.h"
class BVHObjectInfo
{
public:
	int id;
	Point3D center;
	BoundingBox bbox;

	BVHObjectInfo(int id, const BoundingBox & bbox);
	~BVHObjectInfo();
};

