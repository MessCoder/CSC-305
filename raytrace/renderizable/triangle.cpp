#include "triangle.h"

Triangle::Triangle(Vec3 a, Vec3 b, Vec3 c, Material material) : Renderizable(material) {
	this->a = a;
	this->b = b;
	this->c = c;
}

bool Triangle::intersect(Ray& ray, float bias) {

	// Who cares (?)
}

void Triangle::rasterize2D(Image& image) {

	// Compute bounds to greatly optimize
	int iMin = 0;
	int iMax = image.cols();
	int jMin = 0;
	int jMax = image.rows();

	float totalArea = get2DArea();

	for (int i = iMin; i < iMax; i++) {
		for (int j = jMin; j < jMax; j++) {

			// Location of fragment in image space
			Vec3 pt = Vec3(((float)i) / image.cols(), ((float)j) / image.rows(), 0.0f);
			pt = 2 * (pt - Vec3(0.5, 0.5, 0));

			float alpha = get2DArea(pt, b, c) / totalArea;
			float beta = get2DArea(a, b, pt) / totalArea;
			float gamma = get2DArea(a, pt, c) / totalArea;

			if (alpha > 0 && alpha < 1
				&& beta > 0 && beta < 1
				&& gamma > 0 && gamma < 1) {
				
				// Render. This- this is gonna be beautiful Morty
				image(j, i) = Vec3(alpha, beta, gamma);
			}
		}
	}
}

float Triangle::get2DArea() {
	return get2DArea(a, b, c);
}

float Triangle::get2DArea(Vec3 a, Vec3 b, Vec3 c) {
	// Formula for flat 2D triangle area:
	// 1/2 (Ax Bx + Bx Cy + Cx Ay - (Ax Cy + Bx Ay + Cx By))
	return 0.5f * (
		a(0) * b(0) + b(0) * c(1) + c(0) * a(1)
		- (a(0) * c(1) + b(0) * a(1) + c(0) * b(1))
		);
}