#ifndef CAMERA_H
#define CAMERA_H

#include "OpenGp/types.h"
using namespace OpenGP;

class Camera
{
public:
    Vec3 e; 
    Vec3 w; 
    Vec3 v; 
    Vec3 u; 
    float d; 

	// e = position
	// w = Forward vector
	// v = Upwards vector
	// u = Rightwards vector
	// d = Focal distance
    Camera(Vec3 e = Vec3(0.0f, 0.0f, -10.0f), // e = -d*w; This will place the pixel grid on the (x = 0, y = 0) plane for convenience
           Vec3 w = Vec3(0.0f, 0.0f, 1.0f),
           Vec3 v = Vec3(0.0f, 1.0f, 0.0f),
           float d = 10.0f,
           int wResolution = 800,
           int hResolution = 600);

    // Call process(row, column, rayOrigin, rayDirection) for a series of rays covering the pixel grid
    void forEachRay(void (*process)(int row, int column, const Vec3 &e, const Vec3 &d));

private:
    int wResolution;
    int hResolution;
    float aspectRatio;
    float left;
    float right;
    float bottom;
    float up;
};

#endif // CAMERA_H
