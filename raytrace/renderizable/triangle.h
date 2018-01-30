#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "renderizable.h"

class Triangle : public Renderizable {
public:
	virtual bool intersect(Ray& ray, float bias = DEFAULT_BIAS);
	
	float get2DArea();
	static float get2DArea(Vec3 a, Vec3 b, Vec3 c);

	// Rasterizes the triangle in the clipping intervals [-1, 1] ignoring the z axis
	void rasterize2D(Image& image);

	Vec3 a;
	Vec3 b;
	Vec3 c;

	// Initializes a triangle in function of it's vertices
	Triangle(Vec3 a, Vec3 b, Vec3 c, Material material);
};

#endif // TRIANGE_H
