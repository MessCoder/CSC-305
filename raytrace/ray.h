#ifndef RAY_H
#define RAY_H

#include "common.h"

class Ray
{
public:
	Vec3 origin;
	Vec3 direction;

	// Raycasting
	bool hit;
	float hitDistance;
	Vec3 hitNormal;

	// Refraction
	float refractivityIndex;
	// This points to a ray entering the object the ray 
	// is currently inside.
	//
	// This allows to easily stack refraction indices.
	Ray* refractionLevelEntry;

	Ray(Vec3 origin, Vec3 direction, float refractivityIndex = 1.0f, Ray* refractionLevelEntry = nullptr);

	Vec3 intersection();
};

#endif // RAY_H
