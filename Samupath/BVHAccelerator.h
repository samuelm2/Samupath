#pragma once
#include "GeometricObject.h"
#include "BVHBuildNode.h"
#include "BVHObjectInfo.h"
#include "LinearBVHNode.h"
#include <vector>
class BVHAccelerator
{
public:
	int max_objs_per_leaf;
	int total_nodes;
	int flatten_bvh(BVHBuildNode* node, int * offset);
	LinearBVHNode* nodes;
	std::vector<GeometricObject*> objs;
	BVHBuildNode* recursive_build(std::vector<BVHObjectInfo> &, int start, int end, int* total_nodes, std::vector<GeometricObject*> & ordered_objs);
	bool hit(const Ray & r, double & min_t, HitInfo & hit_info) const;

	BVHAccelerator(std::vector<GeometricObject*> & objs, int max_objs_per_leaf);
	BVHAccelerator();
	~BVHAccelerator();
};

