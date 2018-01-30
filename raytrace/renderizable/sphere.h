#ifndef SPHERE_H
#define SPHERE_H

#include "renderizable.h"

class Sphere : public Renderizable {
public:
	virtual bool intersect(Ray& ray, float bias = DEFAULT_BIAS);

	Vec3 pos;
	float radious;

	Sphere(Vec3 pos, float radious, Material material);
};

#endif // SPHERE_H
