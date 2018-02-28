
#include "CubeBuilder.h"

void CubeBuilder::_build() {
	
	// Add front side
	Vec3 normal(0, 0, -1);
	addVertex(Vec3(-1, -1, -1), normal, Vec2(1./4., 1./3.));
	addVertex(Vec3(1, -1, -1), normal, Vec2(2./4., 1./3.));
	addVertex(Vec3(-1, 1, -1), normal, Vec2(1./4., 2./3.));
	addVertex(Vec3(1, 1, -1), normal, Vec2(2./4., 2./3.));
	makeQuad(0, 1, 2, 3);

	// Add bottom side
	normal = Vec3(0, -1, 0);
	addVertex(Vec3(-1, -1, 1), normal, Vec2(1. / 4., 0));
	addVertex(Vec3(1, -1, 1), normal, Vec2(2. / 4., 0));
	addVertex(Vec3(-1, -1, -1), normal, Vec2(1. / 4., 1. / 3.));
	addVertex(Vec3(1, -1, -1), normal, Vec2(2. / 4., 1. / 3.));
	makeQuad(4, 5, 6, 7);

	// Add right side
	normal = Vec3(1, 0, 0);
	addVertex(Vec3(1, -1, -1), normal, Vec2(2. / 4., 1. / 3.));
	addVertex(Vec3(1, -1, 1), normal, Vec2(3. / 4., 1. / 3.));
	addVertex(Vec3(1, 1, -1), normal, Vec2(2. / 4., 2. / 3.));
	addVertex(Vec3(1, 1, 1), normal, Vec2(3. / 4., 2. / 3.));
	makeQuad(8, 9, 10, 11);

	// Add top side
	normal = Vec3(0, 1, 0);
	addVertex(Vec3(-1, 1, -1), normal, Vec2(1. / 4., 2. / 3.));
	addVertex(Vec3(1, 1, -1), normal, Vec2(2. / 4., 2. / 3.));
	addVertex(Vec3(-1, 1, 1), normal, Vec2(1. / 4., 1));
	addVertex(Vec3(1, 1, 1), normal, Vec2(2. / 4., 1));
	makeQuad(12, 13, 14, 15);

	// Add left side
	normal = Vec3(-1, 0, 0);
	addVertex(Vec3(-1, -1, 1), normal, Vec2(0, 1. / 3.));
	addVertex(Vec3(-1, -1, -1), normal, Vec2(1. / 4., 1. / 3.));
	addVertex(Vec3(-1, 1, 1), normal, Vec2(0, 2. / 3.));
	addVertex(Vec3(-1, 1, -1), normal, Vec2(1. / 4., 2. / 3.));
	makeQuad(16, 17, 18, 19);

	// Add back side
	normal = Vec3(0, 0, 1);
	addVertex(Vec3(1, -1, 1), normal, Vec2(3. / 4., 1. / 3.));
	addVertex(Vec3(-1, -1, 1), normal, Vec2(1, 1. / 3.));
	addVertex(Vec3(1, 1, 1), normal, Vec2(3. / 4., 2. / 3.));
	addVertex(Vec3(-1, 1, 1), normal, Vec2(1, 2. / 3.));
	makeQuad(20, 21, 22, 23);
}
