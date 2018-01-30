#ifndef RENDERIZABLE_H
#define RENDERIZABLE_H

#include "../common.h"

#include "../ray.h"
#include "../scene.h"
#include "material/material.h"

class Renderizable {
public:
	Material material;

	// e = ray origin
	// d = ray direction
	// i = intersection
	// n = normal
    virtual bool intersect(Ray& ray, float bias = DEFAULT_BIAS) = 0;
	
	// lights = all lights to process
	// e = ray origin
	// d = ray direction
	// i = intersection
	// n = normal
	Colour getHitColour(Scene& scene, Ray& ray, float bias = DEFAULT_BIAS, int depth = 0) const;

	Renderizable(Material material);
};

#endif // RENDERIZABLE_H
