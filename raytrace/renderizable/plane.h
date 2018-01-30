#ifndef PLANE_H
#define PLANE_H

#include "renderizable.h"

class Plane : public Renderizable {
public:
	virtual bool intersect(Ray& ray, float bias = DEFAULT_BIAS);

	Vec3 normal;
	float distToOrigin;

	Plane(Vec3 normal, float distToOrigin, Material material);
};

#endif // PLANE_H
