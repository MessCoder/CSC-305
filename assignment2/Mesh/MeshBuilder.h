#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "../common.h"

class MeshBuilder {
public:
	void build(Mesh& mesh);

protected:
	// Build the mesh using this interface
	virtual void _build() = 0;

	// Adds a vertex with the given properties
	void addVertex(Vec3 pos, Vec3 normal, Vec2 uv);
	
	// Makes a triangle with the given vertices.
	// a, b and c must be specified in closkwise order from the side that the
	// normal points to.
	void makeTri(unsigned int a, unsigned int b, unsigned int c);
	
	// Makes a quad with the given vertices.
	// a = lower left
	// b = lower right
	// c = upper left
	// d = upper right
	void makeQuad(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

	std::vector<Vec3> vertices;
	std::vector<Vec3> normals;
	std::vector<Vec2> textCoords;
	std::vector<unsigned int> triangles;
};

#endif // !MESH_BUILDER_H