#include "ray.h"

Ray::Ray(Vec3 origin, Vec3 direction) {
	this->origin = origin;
	this->direction = direction;

	this->hit = false;
	this->hitDistance = std::numeric_limits<float>::infinity();
	this->hitNormal = Vec3(0.0f, 0.0f, 0.0f);
}

Vec3 Ray::intersection() {

	if (!this->hit) {
		throw std::invalid_argument("Can't get intersection of a ray that hasn't hit anything");
	}

	return this->origin + this->direction * this->hitDistance;
}