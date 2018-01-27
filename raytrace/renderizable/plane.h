#ifndef PLANE_H
#define PLANE_H

#include "renderizable.h"

class Plane : public Renderizable {
public:
	virtual bool intersect(const Vec3 &e, const Vec3 &d, Vec3 &intersection, Vec3 &normal) const;

	Vec3 normal;
	float distToOrigin;

	Plane(Vec3 normal, float distToOrigin, Material material);
};

#endif // PLANE_H
