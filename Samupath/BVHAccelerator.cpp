#include "pch.h"
#include "BVHAccelerator.h"
#include "MidpointComparer.h"
#include <iostream>


BVHBuildNode * BVHAccelerator::recursive_build(std::vector<BVHObjectInfo>& build_data, int start, int end, int * total_nodes, std::vector<GeometricObject*>& ordered_objs)
{
	(*total_nodes)++;
	BVHBuildNode *node = new BVHBuildNode();

	BoundingBox bbox = build_data[start].bbox;
	for (int i = start; i < end; i++) {
		bbox = bbox.union_boxes(build_data[i].bbox);
	}

	int num_objs = end - start;
	if (num_objs <= max_objs_per_leaf) {
		int obj_offset = ordered_objs.size();
		for (int i = start; i < end; i++) {
			int obj_id = build_data[i].id;
			ordered_objs.push_back(objs[obj_id]);
		}
		node->init_leaf(obj_offset, num_objs, bbox);
	}
	else {
		BoundingBox centroidBounds = BoundingBox();
		for (int i = start; i < end; i++) {
			centroidBounds = centroidBounds.union_boxes(build_data[i].center);
		}
		int dim = centroidBounds.get_extent();
		if (centroidBounds.max[dim] == centroidBounds.min[dim]) {
			int obj_offset = ordered_objs.size();
			for (int i = start; i < end; i++) {
				int obj_id = build_data[i].id;
				if (obj_id == 2935) {
				}
				ordered_objs.push_back(objs[obj_id]);
			}
			node->init_leaf(obj_offset, num_objs, bbox);
			return node;
		}

		double mid = .5 * (centroidBounds.min[dim] + centroidBounds.max[dim]);
		BVHObjectInfo* mid_info = std::partition(&build_data[start], &build_data[end - 1] + 1, MidpointComparer(dim, mid));
		int mid_index = mid_info - &build_data[0];
		node->init_interior(dim, recursive_build(build_data, start, mid_index, total_nodes, ordered_objs), recursive_build(build_data, mid_index, end, total_nodes, ordered_objs));
	}
	return node;
}

bool BVHAccelerator::hit(const Ray & r, double & min_t, HitInfo & hit_info) const
{
	if (total_nodes == 0) {
		return false;
	}
	bool hit = false;
	Direction inverse_direction = 1. / r.direction;
	int negative_dir[3] = { inverse_direction.x < 0, inverse_direction.y < 0, inverse_direction.z < 0 };
	int todo_offset = 0, node_num = 0;
	int todo[64];
	
	double curr_t = MAX_DOUBLE;
	double minimum_t = MAX_DOUBLE;
	Material* curr = nullptr;
	Direction curr_normal = Direction();
	Point2D currUV = Point2D();
	//std::cout << "entering loop" << std::endl;
	while (true) {
		const LinearBVHNode *node = &nodes[node_num];
		//std::cout << (int)node->num_objs << std::endl;
		if (node->bbox.hit(r, min_t, hit_info)) {
			if (node->num_objs > 0) {
				
				//std::cout << "checking children" << std::endl;
				for (int i = 0; i < node->num_objs; i++) {
					if (objs[node->obj_offset + i]->hit(r, curr_t, hit_info) && curr_t < minimum_t && curr_t > 0) {
						minimum_t = curr_t;
						curr = hit_info.material;
						curr_normal = hit_info.normal;
						currUV = hit_info.uv;
						hit = true;

					}
				}
				if (todo_offset == 0) break;
				node_num = todo[--todo_offset];
			}
			else {
				
				if (negative_dir[node->axis]) {
					//std::cout << "traversing child1" << std::endl;
					todo[todo_offset++] = node_num + 1;
					node_num = node->child_offset;
				}
				else {
					//std::cout << "traversing child2" << std::endl;
					todo[todo_offset++] = node->child_offset;
					node_num = node_num + 1;
				}
			}
		}
		else {
			if (todo_offset == 0) break;
			node_num = todo[--todo_offset];
		}
	}
	hit_info.did_hit = hit;
	hit_info.hit_point = r.origin + minimum_t * r.direction;
	hit_info.material = curr;
	hit_info.normal = curr_normal;
	hit_info.uv = currUV;
	min_t = minimum_t;


	return hit;
}

int BVHAccelerator::flatten_bvh(BVHBuildNode * node, int * offset)
{
	LinearBVHNode* linear_node = &nodes[*offset];
	linear_node->bbox = node->bounds;
	int local_offset = *offset;
	*offset = *offset + 1;

	//if node is a child
	if (node->num_objs > 0) {
		linear_node->obj_offset = node->first_obj_offset;
		linear_node->num_objs = node->num_objs;
	}
	else {
		linear_node->axis = node->split_axis;
		linear_node->num_objs = 0;
		flatten_bvh(node->children[0], offset);
		linear_node->child_offset = flatten_bvh(node->children[1], offset);
	}
	return local_offset;
}


BVHAccelerator::BVHAccelerator(std::vector<GeometricObject*>& objs, int max_objs_per_leaf) : max_objs_per_leaf(max_objs_per_leaf)
{
	std::vector<BVHObjectInfo> build_data;
	build_data.reserve(objs.size());
	for (int i = 0; i < objs.size(); i++) {
		BoundingBox bbox = objs[i]->getBBox();
		build_data.push_back(BVHObjectInfo(i, bbox));
	}
	this->objs = objs;
	int total_nodes = 0;
	std::vector<GeometricObject*> ordered_objs;
	ordered_objs.reserve(objs.size());
	std::cout << "Num triangles: " << objs.size() << std::endl;
	BVHBuildNode* root = recursive_build(build_data, 0, objs.size(), &total_nodes, ordered_objs);
	nodes = new LinearBVHNode[total_nodes];
	this->total_nodes = total_nodes;

	int offset = 0;
	flatten_bvh(root, &offset);
	this->objs = ordered_objs;

}

BVHAccelerator::BVHAccelerator()
{
}

BVHAccelerator::~BVHAccelerator()
{
}
