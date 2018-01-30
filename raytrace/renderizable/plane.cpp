#include "plane.h"

Plane::Plane(Vec3 normal, float distToOrigin, Material material) : Renderizable(material)
{
	this->normal = normal;
	this->distToOrigin = distToOrigin;
}

bool Plane::intersect(Ray& ray, float bias)
{
	Vec3 pointInPlane = this->normal * distToOrigin;
	
	float distance = (pointInPlane - ray.origin).dot(this->normal);
	distance /= ray.direction.dot(this->normal);

	if (distance >= bias) {
		ray.hit = true;
		ray.hitDistance = distance;
		ray.hitNormal = this->normal;

		return true;
	}
	else {
		return false;
	}
}
