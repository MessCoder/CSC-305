#include "camera.h"

Camera::Camera(Vec3 e, Vec3 w, Vec3 v, float d, int hResolution, int wResolution) {

    this->e = e;
    this->w = w;
    this->v = v;
    this->u = v.cross(w).normalized();
	this->d = d;

	this->setResolution(hResolution, wResolution);
}

void Camera::setResolution(int hResolution, int wResolution) {
	
	this->image = Image(hResolution, wResolution);

	this->aspectRatio = float(wResolution) / float(hResolution);
	this->left = -1.0f * aspectRatio;
	this->right = 1.0f * aspectRatio;
	this->bottom = -1.0f;
	this->up = 1.0f;
}

Image& Camera::render(Scene& scene, int antialising) {

	image.setConstant(BLACK);

	// Size of the ray matrix to render taking antialising into account
	int hRays = image.rows() * antialising;
	int wRays = image.cols() * antialising;
	float rayColourFactor = 1.0f / std::powf(antialising, 2);

	// Place the initial position at the given focal distance
	Vec3 currentRowStart = w * d;

	// Place the initial position in the center of the first column
	Vec3 wStep = (right - left) / float(wRays) * u;
	currentRowStart += left * u + 0.5f * wStep;

	// Place the initial position in the center of the first row
	Vec3 hStep = (up - bottom) / float(hRays) * v;
	currentRowStart += bottom * v + 0.5f * hStep;

	for (int row = 0; row < hRays; ++row) {

		if (row % 5 == 0) {
			std::cout << "Rendering row number: " << row << std::endl;
		}

		// Use a different vector to iterate through the row
		Vec3 pos = currentRowStart;
		for (int column = 0; column < wRays; ++column) {

			// Build the ray associated to this position
			Vec3 direction = (pos).normalized();
			Ray ray(e, direction);

			// Obtain and set the color for that ray in the current scene
			Colour colour = scene.getHitColour(ray);
			image(row / antialising, column / antialising) += colour * rayColourFactor;

			// Update the pixel position, move it one position right
			pos += wStep;
		}

		// Update the row start, move it one position up
		currentRowStart += hStep;
	}

	return this->image;
}
