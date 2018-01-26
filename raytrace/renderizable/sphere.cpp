#include "sphere.h"

Sphere::Sphere(Vec3 pos, float radious, Material material) : Renderizable(material)
{
	this->pos = pos;
	this->radious = radious;
}

bool Sphere::intersect(const Vec3& e, const Vec3& d, Vec3& intersection, Vec3& normal) const
{
	Vec3 sphereToE = e - pos;
	float dDotSphereToE = d.dot(sphereToE);

	float disc = std::powf(dDotSphereToE, 2) - sphereToE.squaredNorm() + std::powf(radious, 2);

	if (disc >= 0) {
		// The ray is hitting the sphere
		float t = -dDotSphereToE - std::sqrtf(disc);
		intersection = e + t * d;
		normal = (intersection - pos) / radious;

		return true;
	}
	else {
		// The ray isn't hitting the sphere
		return false;
	}
}
