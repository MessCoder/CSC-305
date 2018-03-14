#pragma once

#include "common.h"

// Class intended for interpolation in cubic bezier curves
class Bezier {
public:
	// Creates a bezier curve 
	//
	// a: origin of the curve
	// b: second interpolation point; initial interpolation direction from a
	// c: third interpolation point; final interpolation direction from d
	// d: end of the curve
	Bezier(Vec2 a, Vec2 b, Vec2 c, Vec2 d);

	// Get a point in the curve, located at a given portion of its length.
	//
	// t: proportion of the complete length of the curve
	// at which the point will be located. [0, 1]
	Vec2 interpolate(float t);

private:
	// origin of the curve
	Vec2 a;

	// second interpolation point; initial interpolation direction from a
	Vec2 b;
	
	// third interpolation point; final interpolation direction from d
	Vec2 c;
	
	// end of the curve
	Vec2 d;
};