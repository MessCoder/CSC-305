#include "material.h"
#include "../../ray.h"
#include "../../scene.h"

Material::Material(Colour colour)
{
	this->colour = colour;
}

Colour Material::getHitColour(Scene& scene, Ray& ray, float bias) const {
	
	Colour result = Colour(0.0f, 0.0f, 0.0f);

	for (auto const light : scene.lights) {
		// Obtain the light vector
		Vec3 dirToLight = (light.pos - ray.intersection()).normalized();

		// Check for shadows
		Ray rayToLight(ray.intersection(), dirToLight);
		scene.castRay(rayToLight, bias);
		
		// The object is lit by the current light
		if (!rayToLight.hit) {

			// Compute the light reflection factor
			float normalToLight = std::fmax(0.0f, ray.hitNormal.dot(dirToLight));

			result += light.intensity * normalToLight * colour;
		}
	}

	// Avoid colours out of bounds
	float x = std::min(result.x(), 1.0f);
	float y = std::min(result.y(), 1.0f);
	float z = std::min(result.z(), 1.0f);
	result = Vec3(x, y, z);

	return result;
}
