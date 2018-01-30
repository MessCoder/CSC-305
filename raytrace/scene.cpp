#include "scene.h"
#include "renderizable\renderizable.h"

Scene::Scene(
	Colour background, 
	std::vector<Light> lights,
	std::vector<Renderizable*> renderizables
) : lights(lights), renderizables(renderizables) {

	this->background = background;
}

Renderizable* Scene::castRay(Ray& ray, float bias) {

	Ray closestHit(ray.origin, ray.direction);
	Renderizable* closestHitRenderizable = nullptr;

	for (Renderizable* renderizable : this->renderizables) {

		renderizable->intersect(ray, bias);

		if (ray.hitDistance < closestHit.hitDistance) {
			closestHit = ray;
			closestHitRenderizable = renderizable;
		}
	}

	ray = Ray(closestHit);
	return closestHitRenderizable;
}

Colour Scene::getHitColour(Ray& ray, float bias) {
	
	Renderizable* renderizable = castRay(ray, bias);

	if (!ray.hit) {
		return this->background;
	}
	else {
		return renderizable->getHitColour(*this, ray);
	}
}