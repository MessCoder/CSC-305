#include "plane.h"

Plane::Plane(Vec3 normal, float distToOrigin, Material material) : Renderizable(material)
{
	this->normal = normal;
	this->distToOrigin = distToOrigin;
}

bool Plane::intersect(const Vec3& e, const Vec3& d, Vec3& intersection, Vec3& normal) const
{
	Vec3 pointInPlane = this->normal * distToOrigin;
	
	float distance = (pointInPlane - e).dot(this->normal);
	distance /= d.dot(this->normal);

	if (distance >= 0) {
		intersection = e + d * distance;
		normal = this->normal;

		return true;
	}
	else {
		return false;
	}
}
