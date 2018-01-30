#include "common.h"
#include "bmpwrite.h"

#include "camera.h"
#include "light.h"
#include "scene.h"

#include "renderizable/renderizable.h"
#include "renderizable/sphere.h"
#include "renderizable/plane.h"

Scene buildScene() {
	Colour background = WHITE;
	
	auto renderizables = std::vector<Renderizable*>();
	auto lights = std::vector<Light>();
	
	renderizables.push_back(
		new Sphere(
			Vec3(-3.0f, 0.0f, 25.0f),
			2.0f,
			Material(Vec3(0.8f, 0.8f, 0.0f))
		)
	);

	renderizables.push_back(
		new Sphere(
			Vec3(1.0f, 1.0f, 25.0f),
			1.5f,
			Material(Vec3(0.8f, 0.8f, 0.0f))
		)
	);

	renderizables.push_back(
		new Plane(
			Vec3(0.0f, 1.0f, 0.0f),
			-1.0f,
			Material(Vec3(0.0f, 0.0f, 1.0f))
		)
	);

	/* Backwards raytracing sphere troubleshooting
	renderizables.push_back(
		new Sphere(
			Vec3(0.0f, 0.0f, -12.0f),
			2.0f,
			Material(RED)
		)
	);
	*/

	lights.push_back(
		Light(
			Vec3(10.0f, 4.0f, 25.0f),
			1.0f
		)
	);

	/*
	lights.push_back(
		Light(
			Vec3(-5.0f, 5.0f, 12.0f),
			0.4f
		)
	);
	*/

	return Scene(background, lights, renderizables);
}

int main(int, char**){

	Scene scene = buildScene();

    Camera camera = Camera(
		Vec3(0.0f, 0.0f, -10.0f), 
		Vec3(0.0f, 0.0f, 1.0f),
		Vec3(0.0f, 1.0f, 0.0f),
		10.0f,
		150 * 9 / 16,
		150);

	Image image = camera.render(scene);

    bmpwrite("../../out.bmp", image);
    OpenGP::imshow(image);

    return EXIT_SUCCESS;
}