#ifndef COMMON_H
#define COMMON_H

#include "OpenGP/Image/Image.h"
#include "OpenGP/types.h"
//#include "Eigen/src/Core/Matrix.h"

using Vec3 = OpenGP::Vec3;

using Colour = Vec3; // RGB Value
#define RED Colour(1.0f, 0.0f, 0.0f)
#define GREEN Colour(0.0f, 1.0f, 0.0f)
#define BLUE Colour(0.0f, 0.0f, 1.0f)
#define LIGHT_BLUE Colour(0.6f, 0.6f, 1.0f)
#define WHITE Colour(1.0f, 1.0f, 1.0f)
#define BLACK Colour(0.0f, 0.0f, 0.0f)

using Image = OpenGP::Image<Colour>;

#define DEFAULT_BIAS 0.01f
#define RAYTRACING_MAX_DEPTH 10
#define MINIMUM_SHADOWED_LIGHT_INTENSITY 0.01f

#endif // COMMON_H