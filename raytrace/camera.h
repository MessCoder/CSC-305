#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"

#include "scene.h"
#include "ray.h"

class Camera
{
public:
	// Camera position
    Vec3 e; 
	// Forward vector
    Vec3 w; 
	// Upwards vector
    Vec3 v; 
	// Rightwards vector
    Vec3 u; 
	// Focal distance
    float d;

	// e = position
	// w = Forward vector
	// v = Upwards vector
	// d = Focal distance
	Camera(
		Vec3 e = Vec3(0.0f, 0.0f, -10.0f), // e = -d*w; This will place the pixel grid on the (x = 0, y = 0) plane for convenience
		Vec3 w = Vec3(0.0f, 0.0f, 1.0f),
		Vec3 v = Vec3(0.0f, 1.0f, 0.0f),
		float d = 10.0f,
		int hResolution = 600,
		int wResolution = 800
	);

	// Updates the image of the camera by casting rays through each pixel and finding the color corresponding
	// to them in function of hits with objects and shading.
	//
	// The antialising parameter indicates the side size of the matrix of rays cast per pixel.
	Image& render(Scene& scene, int antialising = 1);

	// Change the camera's resolution
	void setResolution(int hResolution, int wResolution);

private:
	Image image;
    float aspectRatio;
    float left;
    float right;
    float bottom;
    float up;
};

#endif // CAMERA_H
