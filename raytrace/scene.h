#ifndef SCENE_H
#define SCENE_H

#include "common.h"

#include "light.h"
#include "ray.h"

class Renderizable;
class Scene
{
public:
	Colour background;
	std::vector<Light> lights;
	std::vector<Renderizable*> renderizables;

	Scene(
		Colour background = Vec3(1.0f, 1.0f, 1.0f),
		std::vector<Light> = std::vector<Light>(), 
		std::vector<Renderizable*> renderizables = std::vector<Renderizable*>()
	);

	// Finds the closest intersection of the passed ray with an object in the scene.
	//
	// The bias parameter defines the minimum distance at which a hit will be considered.
	Renderizable* castRay(Ray& ray, float bias = DEFAULT_BIAS);

	// Finds the closest intersection of the passed ray with an object in the scene 
	// and returns the perceived colour.
	//
	// The bias parameter defines the minimum distance at which a hit will be considered.
	Colour getHitColour(Ray& ray, float bias = DEFAULT_BIAS, int depth = 0);
};

#include "renderizable/renderizable.h"

#endif // SCENE_H
