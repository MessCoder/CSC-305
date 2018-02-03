#include "material.h"
#include "material.h"
#include "../../ray.h"
#include "../../scene.h"
#include <math.h>

Material::Material(Colour colour, float reflectivity, float refractivity, float refractivityIndex)
{
	this->colour = colour;
	this->reflectivity = reflectivity;
	this->refractivity = refractivity;
	this->refractivityIndex = refractivityIndex;
}

Colour Material::getHitColour(Scene& scene, Ray& ray, float bias, int depth) const {
	
	Colour result = Colour(0.0f, 0.0f, 0.0f);

	if (reflectivity < 1.0f && refractivity < 1.0f) {
		applyShading(scene, ray, bias, result);
	}

	if (reflectivity > 0) {
		applyReflection(ray, scene, bias, depth, result);
	}

	if (refractivity > 0) {
		applyRefraction(ray, scene, bias, depth, result);
	}

	// Avoid colours out of bounds
	float x = std::min(result.x(), 1.0f);
	float y = std::min(result.y(), 1.0f);
	float z = std::min(result.z(), 1.0f);
	result = Vec3(x, y, z);

	return result;
}

void Material::applyShading(Scene & scene, Ray & ray, float bias, Colour &result) const
{
	for (auto const light : scene.lights) {

		// Obtain the light vector
		Vec3 vecToLight = light.pos - ray.intersection();
		Vec3 dirToLight = (vecToLight).normalized();
		float distToLight = vecToLight.norm();

		// Check for shadows
		Ray rayToLight(ray.intersection(), dirToLight);

		std::vector<std::pair<Ray, Renderizable*>> hits;
		scene.getRaycastHits(rayToLight, hits, bias);

		// As there are refractive materials, we need to check for transparency
		// We start with the colour of the material;
		Colour lightFilter = colour;
		for (auto const hit : hits) {

			// If the hit is not beyond the light, reduce the light intensity
			// in function of the hit object's transparency and colour.
			if (hit.first.hitDistance < distToLight) {

				float refractivity = hit.second->material.refractivity;
				if (refractivity == 0.0f) {
					lightFilter = BLACK;
					break;
				}

				// As we move from refractivity 0 to 0.5, we add a filter coloured as the 
				// hit object.
				Colour colourFilter = std::fmin(refractivity, 0.5f) * hit.second->material.colour;
				
				// As we move from refractivity 0.5 to 1, we interpolate to white.
				colourFilter += std::fmax(refractivity - 0.5f, 0.0f) * (WHITE - hit.second->material.colour);

				colourFilter *= 2;
				
				// We apply the filter to the current light
				lightFilter = Vec3(
					lightFilter(0) * colourFilter(0),
					lightFilter(1) * colourFilter(1),
					lightFilter(2) * colourFilter(2)
				);
			}

			if (lightFilter(0) > MINIMUM_SHADOWED_LIGHT_INTENSITY 
				|| lightFilter(1) > MINIMUM_SHADOWED_LIGHT_INTENSITY
				|| lightFilter(2) > MINIMUM_SHADOWED_LIGHT_INTENSITY) {

				break;
			}
		}

		if (lightFilter(0) > MINIMUM_SHADOWED_LIGHT_INTENSITY
			|| lightFilter(1) > MINIMUM_SHADOWED_LIGHT_INTENSITY
			|| lightFilter(2) > MINIMUM_SHADOWED_LIGHT_INTENSITY) {

			// Compute the shading factor
			float normalToLight = std::fmax(0.0f, ray.hitNormal.dot(dirToLight));

			// Add the light
			result += light.intensity * normalToLight * lightFilter;
		}
	}
}

void Material::applyReflection(Ray & ray, Scene & scene, float bias, int depth, Colour &result) const
{
	Vec3 reflectionDir = -ray.direction + 2 * (ray.hitNormal - (-ray.direction));
	reflectionDir = reflectionDir.normalized();
	//Vec3 reflectionDir(0.0f, 1.0f, 0.0f);
	Ray reflectionRay(ray.intersection(), reflectionDir, ray.refractivityIndex, ray.refractionLevelEntry);

	Colour reflectionColour = scene.getHitColour(reflectionRay, bias, depth);

	result = result * (1 - reflectivity) + reflectionColour * reflectivity;
}

void Material::applyRefraction(Ray & ray, Scene & scene, float bias, int depth, Colour &result) const
{
	// Warning: This method is Huge.
	Vec3 direction = ray.direction;
	Vec3 normal = ray.hitNormal;
	float incidenceProjection = direction.dot(normal);

	Ray* refractionLevelEntry;
	float lastRefractivityIndex;
	float newRefractivityIndex;

	// The ray is entering the object
	if (incidenceProjection < 0) {
		// We update the normal used in the refracted ray computation 
		// to point in the opposite direction.
		normal = -normal;
		// We update the incidence projection to reflect that change.
		incidenceProjection = -incidenceProjection;

		// We setup the ray linked list to store the correct refractivity
		// indexes.

		// A ray that just entered an object must point to the entering 
		// ray
		refractionLevelEntry = &ray;
		
		// We're entering an object, ray was outside and contains the
		// previous refractivity index.
		lastRefractivityIndex = refractionLevelEntry == nullptr ?
			1.0f : refractionLevelEntry->refractivityIndex;

		// The new medium is the object, the new index is the object's
		newRefractivityIndex = this->refractivityIndex;
	}
	// The ray is exiting the object
	else {
		// There is no need to modify the normal or direction used in the
		// refracted ray computation.
		
		// We setup the ray linked list to store the correct refractivity
		// indexes.

		// A ray that just exited an object must point to the ray 
		// entering the current medium, that's two jumps, the ray 
		// pointed by the ray pointed by the passed ray.
		refractionLevelEntry = ray.refractionLevelEntry == nullptr ?
			ray.refractionLevelEntry : 
			ray.refractionLevelEntry->refractionLevelEntry;

		// We're exiting the hit object, so the previous refractivity
		// index is that object's
		lastRefractivityIndex = this->refractivityIndex;
		
		// If we have a reference to the ray entering the medium
		// we're entering, we use it.
		//
		// That's one jump, ray is inside the medium we're exiting, 
		// the previous one was in the medium we're going back to.
		newRefractivityIndex = ray.refractionLevelEntry == nullptr ?
			1.0f : ray.refractionLevelEntry->refractivityIndex;
	}

	float incidenceAngle = std::acosf(incidenceProjection / (direction.norm() * normal.norm()));
	Vec3 rotationAxis = -direction.cross(normal).normalized();

	// Obtain the refraction direction in function of the previous information
	//
	// Get the rotation matrix for the refraction
	float refractionAngle = std::asinf(
		lastRefractivityIndex / newRefractivityIndex * std::sinf(incidenceAngle)
	);

	// Get the actual refraction direction
	auto rotation = Eigen::AngleAxis<float>(refractionAngle, rotationAxis).toRotationMatrix();
	Vec3 refractionDir = rotation * (normal);

	// Build the ray
	Ray refractionRay(ray.intersection(), refractionDir, refractivityIndex, refractionLevelEntry);

	// Finally use that ray
	Colour refractionColour = scene.getHitColour(refractionRay, bias, depth);

	// Add the refraction to the pixel
	result = result * (1 - refractivity) + refractionColour * refractivity;
}
