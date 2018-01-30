#ifndef MATERIAL_H
#define MATERIAL_H

#include "../../common.h"

class Scene;
class Ray;

class Material
{
public:
	Colour colour;
	float reflectivity;

    // e = ray origin
    // d = ray direction
    // i = intersection
    // n = normal
	Colour getHitColour(Scene& scene, Ray& ray, float bias = DEFAULT_BIAS, int depth = 0) const;
	
	Material(Colour colour = RED, float reflectivity = 0.0f);
};

#endif // MATERIAL_H
