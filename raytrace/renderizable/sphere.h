#ifndef SPHERE_H
#define SPHERE_H

#include "renderizable.h"

class Sphere : public Renderizable {
public:
	virtual bool intersect(const Vec3 &e, const Vec3 &d, Vec3 &intersection, Vec3 &normal) const;

	Vec3 pos;
	float radious;

	Sphere(Vec3 pos, float radious, Material material);
};

#endif // SPHERE_H
