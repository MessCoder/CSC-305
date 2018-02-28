
#include "MeshBuilder.h"

void MeshBuilder::build(Mesh& mesh) {
	
	mesh.init();

	this->_build();

	mesh.loadVertices(vertices, triangles);
	mesh.loadNormals(normals);
	mesh.loadTexCoords(textCoords);
}

void MeshBuilder::addVertex(Vec3 pos, Vec3 normal, Vec2 uv) {
	vertices.push_back(pos);
	normals.push_back(normal);
	textCoords.push_back(uv);
}

void MeshBuilder::makeTri(unsigned int a, unsigned int b, unsigned int c) {

	triangles.push_back(a);
	triangles.push_back(b);
	triangles.push_back(c);
}

void MeshBuilder::makeQuad(unsigned int a, unsigned int b, unsigned int c, unsigned int d) {

	makeTri(a, d, b);
	makeTri(a, c, d);
}