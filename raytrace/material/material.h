#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>
#include "OpenGp/types.h"
using namespace OpenGP;
using Colour = Vec3; // RGB Value

#include "../light.h"

class Material
{
public:
    Colour colour;

    // e = ray origin
    // d = ray direction
    // i = intersection
    // n = normal
    Colour getHitColour(std::vector<Light> lights, const Vec3& e, const Vec3& d, const Vec3& i, const Vec3& n) const;
	
	Material(Colour colour);
};

#endif // MATERIAL_H
