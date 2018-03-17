
#include "bezier.h"

Bezier::Bezier(Vec2 a, Vec2 b, Vec2 c, Vec2 d) {
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
};

Bezier::Bezier() {
	this->a = Vec2(1., 1.);
	this->b = Vec2(1., 1.);
	this->c = Vec2(1., 1.);
	this->d = Vec2(1., 1.);
};

Vec2 Bezier::interpolate(float t) {
	// The senseless optimization devil has hit me

	// Powers of t
	auto t2 = t * t;
	auto t3 = t2 * t;
	
	// Powers of (1 - t)
	auto oppT = 1 - t;
	auto oppT2 = oppT * oppT;
	auto oppT3 = oppT2 * oppT;
	
	// Factors of points
	auto factor1 = oppT3;
	auto factor2 = 3 * oppT2 * t;
	auto factor3 = 3 * oppT * t2;
	auto factor4 = t3;

	Vec2 result(
		factor1 * a.x() + factor2 * b.x() + factor3 * c.x() + factor4 * d.x(),
		factor1 * a.y() + factor2 * b.y() + factor3 * c.y() + factor4 * d.y()
	);

	return result;
};