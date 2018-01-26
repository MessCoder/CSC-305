#include "material.h"

Material::Material(Colour colour)
{
	this->colour = colour;
}

Colour Material::getHitColour(std::vector<Light> lights, const Vec3& e, const Vec3& d, const Vec3& i, const Vec3& n) const {
	Colour result = Colour(0.0f, 0.0f, 0.0f);

	for (auto const light : lights) {
		// Obtain the light vector
		Vec3 l = (light.pos - i).normalized();
		float normalToLight = std::fmax(0.0f, n.dot(l));

		result += light.intensity * normalToLight * colour;
	}

	// Avoid colours out of bounds
	float x = std::min(result.x(), 1.0f);
	float y = std::min(result.y(), 1.0f);
	float z = std::min(result.z(), 1.0f);
	result = Vec3(x, y, z);

	return result;
}
