#include "camera.h"

Camera::Camera(Vec3 e, Vec3 w, Vec3 v, float d, int wResolution, int hResolution) {

    this->e = e;
    this->w = w;
    this->v = v;
    this->u = v.cross(w).normalized();

    this->wResolution = wResolution;
    this->hResolution = hResolution;
    this->aspectRatio = float(wResolution) / float(hResolution);
    this->left = -1.0f * aspectRatio;
    this->right = 1.0f * aspectRatio;
    this->bottom = -1.0f;
    this->up = 1.0f;
}

void Camera::forEachRay(void (*process)(int row, int column, const Vec3 &e, const Vec3 &d)) {

    // Place the initial position in the center of the first column
    Vec3 wStep = (right-left) / float(wResolution) * u;
    Vec3 currentRowStart = left * u + 0.5f * wStep;

    // Place the initial position in the center of the first row
    Vec3 hStep = (up-bottom) / float(hResolution) * v;
    currentRowStart += bottom * v + 0.5f * hStep;

    for (int row = 0; row < hResolution; ++row) {
		
		// Use a different vector to iterate through the row
		Vec3 pixelPos = currentRowStart;
		for (int column = 0; column < wResolution; ++column) {

            Vec3 d = (pixelPos - e).normalized();
            process(row, column, e, d);

            // Update the pixel position, move it one position right
            pixelPos += wStep;
        }

        // Update the row start, move it one position up
        currentRowStart += hStep;
    }
}
