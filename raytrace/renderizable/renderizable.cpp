#include "renderizable.h"

Renderizable::Renderizable(Material material) : material(material) {
}

Colour Renderizable::getHitColour(std::vector<Light> lights, const Vec3& e, const Vec3& d, const Vec3& i, const Vec3& n) const {
	return material.getHitColour(lights, e, d, i, n);
}