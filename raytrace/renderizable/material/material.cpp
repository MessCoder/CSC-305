#include "material.h"
#include "../../ray.h"
#include "../../scene.h"

Material::Material(Colour colour, float reflectivity)
{
	this->colour = colour;
	this->reflectivity = reflectivity;
}

Colour Material::getHitColour(Scene& scene, Ray& ray, float bias, int depth) const {
	
	Colour result = Colour(0.0f, 0.0f, 0.0f);

	if (reflectivity < 1.0f) {
		for (auto const light : scene.lights) {
			
			// Obtain the light vector
			Vec3 vecToLight = light.pos - ray.intersection();
			Vec3 dirToLight = (vecToLight).normalized();

			// Check for shadows
			Ray rayToLight(ray.intersection(), dirToLight);
			scene.castRay(rayToLight, bias);

			// The object is lit by the current light
			if (!rayToLight.hit || std::powf(rayToLight.hitDistance, 2) > vecToLight.squaredNorm()) {

				// Compute the shading factor
				float normalToLight = std::fmax(0.0f, ray.hitNormal.dot(dirToLight));

				result += light.intensity * normalToLight * colour;
			}
		}
	}

	// Add reflection
	if (reflectivity > 0) {

		Vec3 reflectionDir = -ray.direction + 2 * (ray.hitNormal - (-ray.direction));
		reflectionDir = reflectionDir.normalized();
		//Vec3 reflectionDir(0.0f, 1.0f, 0.0f);
		Ray reflectionRay(ray.intersection(), reflectionDir);

		Colour reflectionColour = scene.getHitColour(reflectionRay, bias, depth);
		
		result = result * (1 - reflectivity) + reflectionColour * reflectivity;
	}

	// Avoid colours out of bounds
	float x = std::min(result.x(), 1.0f);
	float y = std::min(result.y(), 1.0f);
	float z = std::min(result.z(), 1.0f);
	result = Vec3(x, y, z);

	return result;
}
