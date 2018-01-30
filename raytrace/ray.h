#ifndef RAY_H
#define RAY_H

#include "common.h"

class Ray
{
public:
	Vec3 origin;
	Vec3 direction;

	bool hit;
	float hitDistance;
	Vec3 hitNormal;

	Ray(Vec3 origin, Vec3 direction);

	Vec3 intersection();
};

#endif // RAY_H
