#include "sphere.h"

Sphere::Sphere(Vec3 pos, float radious, Material material) : Renderizable(material)
{
	this->pos = pos;
	this->radious = radious;
}

bool Sphere::intersect(Ray& ray, float bias)
{
	Vec3 originToSphere = pos - (ray.origin + ray.direction * bias);
	float centerProjection = ray.direction.dot(originToSphere);

	// We check the camera is not facing the opposite way (from outside the sphere)
	float originToSphereSqrNorm = originToSphere.squaredNorm();
	float sqrRadious = std::powf(radious, 2);
	if (centerProjection < 0 && originToSphereSqrNorm >= sqrRadious) {
		return false;
	}

	// The discriminant measures two things the square of the distance 
	// between the projection of the sphere centre on the ray.
	//
	// A distance = 0 will mean there is one and only one intersection.
	// A distance > 0 will mean there are two intersections.
	float discriminant = 
		std::powf(centerProjection, 2) 
		- originToSphereSqrNorm
		+ sqrRadious;

	if (discriminant >= 0) {

		// The ray is hitting the sphere
		ray.hit = true;

		// There may be two intersections and we want to pick the closest.
		//
		// The first option to pick would be centerProjection - sqrt(disc),
		// but this may be negative, so we check for that.
		float projectionToIntersection = std::sqrtf(discriminant);
		ray.hitDistance = centerProjection - projectionToIntersection;

		if (ray.hitDistance < 0) {
			ray.hitDistance += 2 * projectionToIntersection;
		}
		
		// Now there's enough information in the ray to compute the 
		// intersection
		ray.hitNormal = (ray.intersection() - pos) / radious;

		return true;
	}
	else {
		// The ray isn't hitting the sphere
		return false;
	}
}
