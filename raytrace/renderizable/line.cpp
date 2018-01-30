#include "line.h"
#include <math.h>

Line::Line(Vec3 a, Vec3 b, Material material) : Renderizable(material) {
	this->a = a;
	this->b = b;
}

void Line::rasterize2D(Image& image) {
	// We're gonna use the Bresenham's line algorithm, using the wikipedia pseudocode
	float deltaX = b(0) - a(0);
	float deltaY = b(1) - a(1);
	float deltaErr = fabsf(deltaY / deltaX);
	float error = 0.0f;

	// Starting coordinates
	int x = (a(0) * 0.5f + 0.5f) * float(image.cols());
	int xMax = (b(0) * 0.5f + 0.5f) * float(image.cols());
	int y = (a(1) * 0.5f + 0.5f) * float(image.rows());

	for (; x <= xMax; x++) {

		image(y, x) = material.colour;

		error += deltaErr;
		while (error >= 0.5f) {
			y += deltaY > 0.0f ? 1 : -1;
			error -= 1.0f;
		}
	}
}