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

void Scene::getRaycastHits(Ray& ray, std::vector<std::pair<Ray, Renderizable*>>& hits, float bias) {
	
	for (Renderizable* renderizable : this->renderizables) {
		Ray currentRay(ray);
		renderizable->intersect(currentRay, bias);

		if (currentRay.hit) {
			auto hit = std::pair<Ray, Renderizable*>(currentRay, renderizable);
			hits.push_back(hit);
		}
	}
}

Colour Scene::getHitColour(Ray& ray, float bias, int depth) {
	
	Renderizable* renderizable = castRay(ray, bias);

	if (!ray.hit) {
		return this->background;
	}
	else {
		depth++;

		if (depth > RAYTRACING_MAX_DEPTH) {
			return background;
		}
		else {
			return renderizable->getHitColour(*this, ray, bias, depth);
		}
	}
}