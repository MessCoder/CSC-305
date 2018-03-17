#include "OpenGP/GL/Eigen.h"
#include "OpenGP/GL/glfw_helpers.h"
#include "Mesh/Mesh.h"

#include "../common.h"
#include "../bezier.cpp"

typedef Eigen::Transform<float,3,Eigen::Affine> Transform;

Mesh arrow;
Mesh satellite;

Bezier arrowTrajectory;
float lastTime = 0.;
float period = 3;

void init();
void display();
void buildArrow();
void buildSatellite();
void buildArrowTrajectory();

int main(int, char**){
    OpenGP::glfwInitWindowSize(512, 512);
	OpenGP::glfwMakeWindow("Planets");
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
	
	

	// **** Arrow transform
	Transform arrow_M = Transform::Identity();
	
	// Position at the correspondent length of the curve
	float t = remainderf(glfwGetTime(), period);
	Vec2 arrowPos = arrowTrajectory.interpolate(t);
	arrow_M *= Eigen::Translation3f(arrowPos.x(), arrowPos.y(), 0.);

	// **** Satellite transform
	Transform satellite_M = Transform::Identity();

	arrow.draw(arrow_M.matrix());
	satellite.draw(satellite_M.matrix());
}

void buildArrow() {
	// The neutral orientation will be to the right
	arrow.init();

	std::vector<OpenGP::Vec3> arrowVertices;
	arrowVertices.push_back(OpenGP::Vec3(-.1, .1, 0.));
	arrowVertices.push_back(OpenGP::Vec3(-.1, -.1, 0.));
	arrowVertices.push_back(OpenGP::Vec3(.1, 0., 0.));

	std::vector<unsigned> arrowIndexes;
	arrowIndexes.push_back(0);
	arrowIndexes.push_back(1);
	arrowIndexes.push_back(2);

	std::vector<OpenGP::Vec2> arrowUv;
	arrowUv.push_back(OpenGP::Vec2(-1., 1.));
	arrowUv.push_back(OpenGP::Vec2(-1., -1.));
	arrowUv.push_back(OpenGP::Vec2(1., 0.));

	arrow.loadVertices(arrowVertices, arrowIndexes);
	arrow.loadTexCoords(arrowUv);
}

void buildSatellite() {
	// The satellite will just be a friggin' square
	satellite.init();

	std::vector<OpenGP::Vec3> quadVert;
	quadVert.push_back(OpenGP::Vec3(-0.1f, -0.1f, 0.0f));
	quadVert.push_back(OpenGP::Vec3(0.1f, -0.1f, 0.0f));
	quadVert.push_back(OpenGP::Vec3(0.1f, 0.1f, 0.0f));
	quadVert.push_back(OpenGP::Vec3(-0.1f, 0.1f, 0.0f));

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
		Vec2(-1.5, -.8),
		Vec2(2., .8),
		Vec2(-2., .8),
		Vec2(1.5, -.8)
	);
};