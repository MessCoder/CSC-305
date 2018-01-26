#ifndef INTERSECTABLE_H
#define INTERSECTABLE_H

#include "OpenGP/types.h"
using namespace OpenGP;

#include "../material/material.h"

class Renderizable {
public:
	// e = ray origin
	// d = ray direction
	// i = intersection
	// n = normal
    virtual bool intersect(const Vec3 &e, const Vec3 &d, Vec3 &i, Vec3 &n) const = 0;
	
	// lights = all lights to process
	// e = ray origin
	// d = ray direction
	// i = intersection
	// n = normal
	Colour getHitColour(std::vector<Light> lights, const Vec3& e, const Vec3& d, const Vec3& i, const Vec3& n) const;

	Material material;

	Renderizable(Material material);
};

#endif // INTERSECTABLE_H
