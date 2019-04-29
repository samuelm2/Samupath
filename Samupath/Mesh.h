#pragma once
#include <string>
#include <vector>
#include "Material.h"
#include "Constants.h"
#include "MeshTriangle.h"


class Mesh
{
public:
	Direction translation;
	double scale;
	Material* material;

	void add_to_world(std::vector<GeometricObject*> & objs);
	Mesh(std::string file_path, Material * material, const Direction & translation, float rotationDegrees, const Direction & rotationDirection, const Direction & scale, bool texture);

private:
	std::vector<MeshTriangle> triangles;
	Mesh();
	~Mesh();
};

