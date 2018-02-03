#include "common.h"
#include "bmpwrite.h"

#include "camera.h"
#include "light.h"
#include "scene.h"

#include "renderizable/renderizable.h"
#include "renderizable/sphere.h"
#include "renderizable/plane.h"

Scene getSpheresScene() {
	Colour background = WHITE;
	
	auto renderizables = std::vector<Renderizable*>();
	auto lights = std::vector<Light>();
	
	// Big left sphere (relfective)
	renderizables.push_back(
		new Sphere(
			Vec3(-3.0f, 0.0f, 25.0f),
			2.0f,
			Material(Vec3(0.8f, 0.8f, 0.0f), 0.7f)
		)
	);

	// Small right sphere
	renderizables.push_back(
		new Sphere(
			Vec3(3.0f, 2.0f, 25.0f),
			1.0f,
			Material(WHITE, 0.1f, 0.1f, 1.5f)
		)
	);

	// Close sphere (refractive)
	renderizables.push_back(
		new Sphere(
			Vec3(1.2f, 0.0f, 17.0f),
			1.0f,
			Material(BLUE, 0.0f, 0.7f, 1.5f)
		)
	);

	// Ground
	renderizables.push_back(
		new Plane(
			Vec3(0.0f, 1.0f, 0.0f),
			-1.0f,
			Material(Vec3(0.0f, 0.0f, 1.0f))
		)
	);
	
	// Background mirror
	renderizables.push_back(
		new Plane(
			Vec3(0.0f, 0.0f, -1.0f),
			-60.0f,
			Material(Vec3(0.15f, 0.15f, 0.0f), 0.2f)
		)
	);
	
	lights.push_back(
		Light(
			Vec3(10.0f, 4.0f, 22.0f),
			1.0f
		)
	);

	lights.push_back(
		Light(
			Vec3(-5.0f, 5.0f, 12.0f),
			0.4f
		)
	);

	return Scene(background, lights, renderizables);
}

Scene getPlaneScene() {
	Colour background = WHITE;

	auto renderizables = std::vector<Renderizable*>();
	auto lights = std::vector<Light>();

	// Mate surface sinking into refractive surface
	renderizables.push_back(
		new Plane(
			Vec3(0.2f, 1.0f, 0.0f).normalized(),
			-10.0f,
			Material(WHITE)
		)
	);
	// Mate horizontal surface under refractive surface
	renderizables.push_back(
		new Plane(
			Vec3(0.0f, 1.0f, 0.0f),
			-14.0f,
			Material(WHITE)
		)
	);
	// Refractive surface
	renderizables.push_back(
		new Plane(
			Vec3(0.0f, 1.0f, 0.0f),
			-10.0f,
			Material(LIGHT_BLUE, 0.0f, 0.9f, 1.3f)
		)
	);


	// Background plane
	renderizables.push_back(
		new Plane(
			Vec3(0.0f, 0.0f, -1.0f),
			-21.0f,
			Material(WHITE)
		)
	);

	lights.push_back(
		Light(
			Vec3(30.0f, 0.0f, 15.0f),
			1.0f
		)
	);

	return Scene(background, lights, renderizables);
}

Scene getHugeSphereScene() {
	Colour background = WHITE;

	auto renderizables = std::vector<Renderizable*>();
	auto lights = std::vector<Light>();

	renderizables.push_back(new Sphere(
		Vec3(0.0f, 0.0f, 0.0f),
		20.0f,
		Material(RED, 0.0f, 0.9f)
	));

	renderizables.push_back(new Sphere(
		Vec3(0.0f, 0.0f, 15.0f),
		1.0f,
		Material(RED)
	));

	lights.push_back(Light(
		Vec3(1.0f, 1.0f, 1.0f).normalized() * 25.0f,
		1.0f
	));

	return Scene(background, lights, renderizables);
}

int main(int, char**){

	Scene scene = getSpheresScene();

    Camera camera = Camera(
		Vec3(0.0f, 0.0f, -10.0f), 
		Vec3(0.0f, 0.0f, 1.0f),
		Vec3(0.0f, 1.0f, 0.0f),
		10.0f,
		800 * 9 / 16,
		800);

	Image image = camera.render(scene, 2);

    bmpwrite("../../out.bmp", image);
    OpenGP::imshow(image);

    return EXIT_SUCCESS;
}