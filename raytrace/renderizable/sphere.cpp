#include "sphere.h"

Sphere::Sphere(Vec3 pos, float radious, Material material) : Renderizable(material)
{
	this->pos = pos;
	this->radious = radious;
}

bool Sphere::intersect(Ray& ray)
{
	Vec3 sphereToE = ray.origin - pos;
	float dDotSphereToE = ray.direction.dot(sphereToE);

	float disc = std::powf(dDotSphereToE, 2) - sphereToE.squaredNorm() + std::powf(radious, 2);

	if (disc >= 0) {
		// The ray is hitting the sphere
		ray.hit = true;
		ray.hitDistance = -dDotSphereToE - std::sqrtf(disc);
		ray.hitNormal = (ray.intersection() - pos) / radious;

		return true;
	}
	else {
		// The ray isn't hitting the sphere
		return false;
	}
}
