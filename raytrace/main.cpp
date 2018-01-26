#include "OpenGP/Image/Image.h"
#include "bmpwrite.h"

#include "camera.h"
#include "light.h"
#include "renderizable/renderizable.h"
#include "renderizable/sphere.h"

using namespace OpenGP;

using Colour = Vec3; // RGB Value
Colour red() { return Colour(1.0f, 0.0f, 0.0f); }
Colour white() { return Colour(1.0f, 1.0f, 1.0f); }
Colour black() { return Colour(0.0f, 0.0f, 0.0f); }

void processRay(int row, int column, const Vec3& e, const Vec3& d);

// Static objects
Image<Colour> image;
Colour background;
Camera camera;

std::vector<Light> lights;
std::vector<Renderizable*> renderizables;

int main(int, char**){

    int wResolution = 500;
    int hResolution = 300;

	background = white();

	image = Image<Colour>(hResolution, wResolution);
	
    camera = Camera(
		Vec3(0.0f, 0.0f, -10.0f), 
		Vec3(0.0f, 0.0f, 1.0f),
		Vec3(0.0f, 1.0f, 0.0f),
		10.0f,
		wResolution,
		hResolution);

	renderizables.push_back(
		new Sphere(
			Vec3(0.0f, 0.0f, 20.0f),
			2.0f,
			Material(red())
		)
	);

    lights.push_back(
        Light(
			Vec3(5.0f, 5.0f, 12.0f), 
			1.0f
		)
    );

    camera.forEachRay(processRay);

    bmpwrite("../../out.bmp", image);
    imshow(image);

    return EXIT_SUCCESS;
}

void processRay(int row, int column, const Vec3 &e, const Vec3 &d) {
	
	for (Renderizable* renderizable : renderizables) {

		Vec3 intersection;
		Vec3 normal;
		bool hit = renderizable->intersect(e, d, intersection, normal);

		if (hit) {
			Colour colour = renderizable->getHitColour(lights, e, d, intersection, normal);
			image(row, column) = colour;
		}
		else {
			image(row, column) = background;
		}
	}
}