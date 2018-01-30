#ifndef LINE_H
#define LINE_H

#include "renderizable.h"

class Line : public Renderizable {
public:
	// Why am I even making this renderizable. It's not.
	virtual bool intersect(Ray& ray, float bias = DEFAULT_BIAS);
	
	// Draw the line in the clipping intervals [-1, 1] ignoring the z axis
	void rasterize2D(Image& image);

	Vec3 a;
	Vec3 b;

	// Initializes a line in function of it's beginning and end
	Line(Vec3 a, Vec3 b, Material material);
};

#endif // LINE_H
