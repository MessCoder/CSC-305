#include "OpenGP/GL/Eigen.h"
#include "OpenGP/GL/glfw_helpers.h"
#include "Mesh/Mesh.h"

#include "../common.h"
#include "../bezier.cpp"

#define _USE_MATH_DEFINES
#include <math.h>

typedef Eigen::Transform<float,3,Eigen::Affine> Transform;

Mesh arrow;
Mesh satellite;
Bezier arrowTrajectory;

// Time taken for the arrow to go along the curve
float arrowPeriod = 3;

// Time taken for the satellite to rotate around 
// the arrow once
float orbitingPeriod = 1;
float orbitSize = 0.2;

// Time taken for the satellite to rotate around
// itself once
float satelliteRotationPeriod = 10;


void init();
void display();
void buildArrow();
void buildSatellite();
void buildArrowTrajectory();
Transform getArrowStepTransform();
Transform getSatelliteStepTransform();

int main(int, char**){
    OpenGP::glfwInitWindowSize(512, 512);
	OpenGP::glfwMakeWindow("Animation");
	OpenGP::glfwDisplayFunc(display);
    init();
	OpenGP::glfwMainLoop();
    return EXIT_SUCCESS;
}

void init(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0);

	// I'm probably actually not going to use this 
	//
    // Enable alpha blending so texture backgroudns remain transparent
    // glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	buildArrow();
	buildSatellite();

	buildArrowTrajectory();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	Transform arrow_M = getArrowStepTransform();
	Transform satellite_M = arrow_M * getSatelliteStepTransform();

	arrow.draw(arrow_M.matrix());
	satellite.draw(satellite_M.matrix());
}

Transform getArrowStepTransform() {

	// Get position information
	float t = fmod(glfwGetTime(), arrowPeriod) / arrowPeriod;
	Vec2 arrowPos = arrowTrajectory.interpolate(t);

	// Get rotation information
	float angle = 0;
	if (t < 0.99) {
		float nextT = t + 0.01;
		Vec2 direction = arrowTrajectory.interpolate(nextT) - arrowPos;
		angle = atan2f(direction.y(), direction.x());
	}

	Transform arrow_M = Transform::Identity();
	arrow_M = Eigen::AngleAxisf(angle, Vec3(0., 0., 1.)).matrix() * arrow_M;
	arrow_M = Eigen::Translation3f(arrowPos.x(), arrowPos.y(), 0.) * arrow_M;

	return arrow_M;
}

Transform getSatelliteStepTransform() {

	// Get the rotation around itself
	float localT = fmod(glfwGetTime(), satelliteRotationPeriod) / satelliteRotationPeriod;
	float localAngle = 2 * M_PI * localT;

	// Get the rotation around the arrow
	float orbitT = fmod(glfwGetTime(), orbitingPeriod) / orbitingPeriod;
	float orbitAngle = 2 * M_PI * orbitT;

	// Build the matrix
	Transform satellite_M = Transform::Identity();
	satellite_M = Eigen::AngleAxisf(localAngle, Vec3(0., 0., 1.)).matrix() * satellite_M;
	satellite_M = Eigen::Translation3f(orbitSize, 0., 0.) * satellite_M;
	satellite_M = Eigen::AngleAxisf(orbitAngle, Vec3(0., 0., 1.)).matrix() * satellite_M;

	return satellite_M;
}

void buildArrow() {
	// The neutral orientation will be to the right
	arrow.init();

	// Curve defining the shape of the arrow
	Bezier curve = Bezier(
		Vec2(-.1, .08),
		Vec2(.12, -.08),
		Vec2(.12, .08),
		Vec2(-.1, -.08)
	);

	// Amount of vertices (must be even)
	int res = 15;

	std::vector<OpenGP::Vec3> arrowVertices;
	std::vector<unsigned> arrowIndexes;
	std::vector<OpenGP::Vec2> arrowUv;

	// Add vertices and uv coordinates as points interpolated
	// by the curve.
	float t = 0;
	float incr = 1. / (res - 1);

	for (int i = 0; i < res; i++, t += incr) {

		Vec2 point = curve.interpolate(t);
		
		arrowVertices.push_back(Vec3(point.x(), point.y(), 0));
		arrowUv.push_back(point);
	}

	// Make the tris!
	//
	// Make rightmost tri
	arrowIndexes.push_back(res/2 - 1);
	arrowIndexes.push_back(res/2);
	arrowIndexes.push_back(res/2 + 1);

	// Make the rest of quads from left to right
	for (int i = 0; i < res; i++) {

		arrowIndexes.push_back(i);
		arrowIndexes.push_back(i + 1);
		arrowIndexes.push_back(res - i - 2);

		arrowIndexes.push_back(i);
		arrowIndexes.push_back(res - i - 2);
		arrowIndexes.push_back(res - i - 1);
	}

	// Actually put it all together
	arrow.loadVertices(arrowVertices, arrowIndexes);
	arrow.loadTexCoords(arrowUv);
}

void buildSatellite() {
	// The satellite will just be a friggin' square
	satellite.init();

	std::vector<OpenGP::Vec3> quadVert;
	quadVert.push_back(OpenGP::Vec3(-0.05f, -0.05f, 0.0f));
	quadVert.push_back(OpenGP::Vec3(0.05f, -0.05f, 0.0f));
	quadVert.push_back(OpenGP::Vec3(0.05f, 0.05f, 0.0f));
	quadVert.push_back(OpenGP::Vec3(-0.05f, 0.05f, 0.0f));

	std::vector<unsigned> quadInd;
	quadInd.push_back(0);
	quadInd.push_back(1);
	quadInd.push_back(2);
	quadInd.push_back(0);
	quadInd.push_back(2);
	quadInd.push_back(3);

	std::vector<OpenGP::Vec2> quadTCoord;
	quadTCoord.push_back(OpenGP::Vec2(0.0f, 0.0f));
	quadTCoord.push_back(OpenGP::Vec2(1.0f, 0.0f));
	quadTCoord.push_back(OpenGP::Vec2(1.0f, 1.0f));
	quadTCoord.push_back(OpenGP::Vec2(0.0f, 1.0f));

	satellite.loadVertices(quadVert, quadInd);
	satellite.loadTexCoords(quadTCoord);
}

void buildArrowTrajectory() {
	
	// We want the arrow to appear from the bottom left, 
	// make a loop in the upper middle, and exit through
	// the bottom right.
	//
	// In order to avoid a very clear effect of the arrow 
	// teleporting from side to side when cycling, we can
	// set the starting and finnish points outside of 
	// clipping space (center - 1.5 -> center + 1.5)
	// 
	// In order to create the loop, the direction pointers
	// must be farther away from the opposite end of the curve
	// (center + 2 -> center - 2)
	
	arrowTrajectory = Bezier(
		Vec2(-1.2, -.8),
		Vec2(2., .8),
		Vec2(-2., .8),
		Vec2(1.2, -.8)
	);
};