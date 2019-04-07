#pragma once
#include <string>
#include <vector>
#include "Material.h"
#include "Constants.h"
#include "Triangle.h"


class Mesh
{
public:
	Direction translation;
	double scale;
	Material* material;

	void add_to_world(std::vector<GeometricObject*> & objs);
	Mesh(std::string file_path, Material * material, const Direction & translation, float rotationDegrees, const Direction & rotationDirection, const Direction & scale);

private:
	std::vector<Triangle> triangles;
	Mesh();
	
	~Mesh();
};

