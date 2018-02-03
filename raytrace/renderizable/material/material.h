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
	float refractivity;
	float refractivityIndex;

    // e = ray origin
    // d = ray direction
    // i = intersection
    // n = normal
	Colour getHitColour(Scene& scene, Ray& ray, float bias = DEFAULT_BIAS, int depth = 0) const;

	Material(Colour colour = RED, float reflectivity = 0.0f, float refractivity = 0.0f, float refractivityIndex = 1.0f);

private:
	void Material::applyShading(Scene & scene, Ray & ray, float bias, Colour &result) const;
	void Material::applyReflection(Ray & ray, Scene & scene, float bias, int depth, Colour &result) const;
	void Material::applyRefraction(Ray & ray, Scene & scene, float bias, int depth, Colour &result) const;
};

#endif // MATERIAL_H
