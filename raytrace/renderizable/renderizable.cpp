#include "renderizable.h"

Renderizable::Renderizable(Material material) : material(material) {
}

Colour Renderizable::getHitColour(Scene& scene, Ray& ray, float bias, int depth) const {
	
	if (!ray.hit) {
		throw std::invalid_argument("Can't get the hit colour of a ray that hasn't hit anything");
	}

	return material.getHitColour(scene, ray, bias, depth);
}