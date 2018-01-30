#ifndef MATERIAL_H
#define MATERIAL_H

#include "../../common.h"

class Scene;
class Ray;

class Material
{
public:
	Vec3 colour;

    // e = ray origin
    // d = ray direction
    // i = intersection
    // n = normal
	Colour getHitColour(Scene& scene, Ray& ray, float bias = DEFAULT_BIAS) const;
	
	Material(Colour colour = RED);
};

#endif // MATERIAL_H
