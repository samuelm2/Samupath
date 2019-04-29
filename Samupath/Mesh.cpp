#include "pch.h"
#include "Mesh.h"
#include "glm/gtc/matrix_transform.hpp"

#define TINYOBJLOADER_USE_DOUBLE
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <iostream>

void Mesh::add_to_world(std::vector<GeometricObject*>& objs)
{
	for (int i = 0; i < triangles.size(); i++) {
		objs.push_back(&triangles[i]);
	}
}

Mesh::Mesh()
{
}

Mesh::Mesh(std::string file_path, Material* material, const Direction & translation, float rotationDegrees, const Direction & rotationDirection, const Direction & scale, bool texture=false)
{
	//auto t = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::dmat4 trans_mat = glm::translate(glm::dmat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1), translation);
	glm::dmat4 scale_mat = glm::scale(trans_mat, scale);
	glm::dmat4 final_mat = glm::rotate(scale_mat, (double)glm::radians(rotationDegrees), rotationDirection);
	

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, file_path.c_str());

	if (!err.empty()) { // `err` may contain warning message.
		std::cerr << err << std::endl;
	}

	if (!ret) {
		exit(1);
	}

	glm::dvec4 temp[3];
	Point3D points[3];
	Point2D uvs[3];
	for (int i = 0; i < 3; i++) {
		temp[i] = glm::dvec4(1.);
		points[i] = Point3D();
	}

	this->triangles = std::vector<MeshTriangle>();

	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			int fv = shapes[s].mesh.num_face_vertices[f];

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				temp[v].x = attrib.vertices[3 * idx.vertex_index + 0];
				temp[v].y = attrib.vertices[3 * idx.vertex_index + 1];
				temp[v].z = attrib.vertices[3 * idx.vertex_index + 2];
				
				temp[v] = final_mat * temp[v];
				points[v].x = temp[v].x;
				points[v].y = temp[v].y;
				points[v].z = temp[v].z;

				uvs[v].x = attrib.texcoords[2 * idx.texcoord_index];
				uvs[v].y = attrib.texcoords[2 * idx.texcoord_index + 1];
			}

			MeshTriangle t = MeshTriangle(points[0], points[1], points[2]);
			t.p1uv = uvs[0];
			t.p2uv = uvs[1];
			t.p3uv = uvs[2];
			t.material = material;

			triangles.push_back(t);

			index_offset += fv;
		}
	}

}

Mesh::~Mesh()
{
}
