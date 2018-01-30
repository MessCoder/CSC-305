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

	// Finds the closest intersection of the passed ray with an object in the scene
	Renderizable* castRay(Ray& ray);

	// Finds the closest intersection of the passed ray with an object in the scene 
	// and returns the perceived colour 
	Colour getHitColour(Ray& ray);
};

#include "renderizable/renderizable.h"

#endif // SCENE_H
