#include <OpenGP/GL/Application.h>
#include "../bezier.cpp"

using namespace OpenGP;

const int width=720, height=720;
#define POINTSIZE 10.0f

const char* line_vshader =
#include "line_vshader.glsl"
;
const char* line_fshader =
#include "line_fshader.glsl"
;

void init();

// Handle for the points composing the skeleton
// and shaping the bezier curve
//
// For changes to make effect, it's required to 
// call refreshLines
std::vector<Vec2> controlPoints;

std::unique_ptr<Shader> lineShader;
std::unique_ptr<GPUMesh> skeleton;
std::unique_ptr<GPUMesh> curve;
std::vector<Vec2> curvePoints;
int curveResolution = 50;

// Updates the OpenGL data for the bezier curve
// and skeleton in function of the current state 
// of controlPoints
void refreshLines();
void initLines();



int main(int, char**){

    Application app;
    init();

    // Mouse position and selected point
    Vec2 position = Vec2(0,0);
    Vec2 *selection = nullptr;

    // Display callback
	Window& window = app.create_window([&](Window&) {
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glPointSize(POINTSIZE);

		lineShader->bind();
		lineShader->set_uniform("selectionColor", Vec3(1, 0, 0));

		// Draw bezier curve skeleton red
		lineShader->set_uniform("selection", -1);
		lineShader->set_uniform("defaultColor", Vec3(0, 0, 1));
		skeleton->set_attributes(*lineShader);
		skeleton->set_mode(GL_LINE_STRIP);
		skeleton->draw();

		// Draw points red and selected point blue
		if (selection != nullptr) lineShader->set_uniform("selection", int(selection - &controlPoints[0]));
		skeleton->set_mode(GL_POINTS);
		skeleton->draw();

		// Draw bezier curve black
		lineShader->set_uniform("selection", -1);
		lineShader->set_uniform("defaultColor", Vec3(0, 0, 0));
		curve->set_attributes(*lineShader);
		curve->set_mode(GL_LINE_STRIP);
		curve->draw();

        lineShader->unbind();
    });
    window.set_title("Bezier editor");
    window.set_size(width, height);

    // Mouse movement callback
    window.add_listener<MouseMoveEvent>([&](const MouseMoveEvent &m){
        // Mouse position in clip coordinates
        Vec2 p = 2.0f*(Vec2(m.position.x()/width,-m.position.y()/height) - Vec2(0.5f,-0.5f));
        if( selection && (p-position).norm() > 0.0f) {
            /// TODO: Make selected control points move with cursor
			selection->x() = position.x();
			selection->y() = position.y();
			refreshLines();
        }
        position = p;
    });

    // Mouse click callback
    window.add_listener<MouseButtonEvent>([&](const MouseButtonEvent &e){
        // Mouse selection case
        if( e.button == GLFW_MOUSE_BUTTON_LEFT && !e.released) {
            selection = nullptr;
            for(auto&& v : controlPoints) {
                if ( (v-position).norm() < POINTSIZE/std::min(width,height) ) {
                    selection = &v;
                    break;
                }
            }
        }
        // Mouse release case
        if( e.button == GLFW_MOUSE_BUTTON_LEFT && e.released) {
            if(selection) {
                selection->x() = position.x();
                selection->y() = position.y();
                selection = nullptr;
				refreshLines();
            }
        }
    });

    return app.run();
}

void init(){
    glClearColor(1,1,1, /*solid*/1.0 );

    lineShader = std::unique_ptr<Shader>(new Shader());
    lineShader->verbose = true;
    lineShader->add_vshader_from_source(line_vshader);
    lineShader->add_fshader_from_source(line_fshader);
    lineShader->link();

    controlPoints = std::vector<Vec2>();
    controlPoints.push_back(Vec2(-0.7f,-0.2f));
    controlPoints.push_back(Vec2(-0.3f, 0.2f));
    controlPoints.push_back(Vec2( 0.3f, 0.5f));
    controlPoints.push_back(Vec2( 0.7f, 0.0f));

	initLines();
}

void refreshLines() {
	// Use the control points as vertices for the curve
	// skeleton
	skeleton->set_vbo<Vec2>("vposition", controlPoints);

	// Interpolate a fixed number of times along the 
	// bezier curve.
	auto interpolator = Bezier(
		controlPoints[0], 
		controlPoints[1], 
		controlPoints[2], 
		controlPoints[3]
	);
	curvePoints = std::vector<Vec2>();
	
	// The last vertex must equal 1, and the first 0, so 
	// the increment is 1 / #segments, not 1 / #vertices
	float tIncrement = 1. / float(curveResolution - 1);

	for (float t = 0; t <= 1; t += tIncrement) {
		Vec2 point = interpolator.interpolate(t);
		curvePoints.push_back(point);
	}
	
	// Use the points to draw the curve
	curve->set_vbo<Vec2>("vposition", curvePoints);
}

void initLines() {

	// We will create the data structures and add fixed 
	// triangle strips to them to... Arrange the lines?
	// Pass safety checks?

	// Skeleton
	skeleton = std::unique_ptr<GPUMesh>(new GPUMesh());
	std::vector<unsigned int> skeletonIndices = { 0,1,2,3 };
	skeleton->set_triangles(skeletonIndices);
	
	// Curve
	curve = std::unique_ptr<GPUMesh>(new GPUMesh());
	std::vector<unsigned int> curveIndices;
	for (int i = 0; i < curveResolution; i++) {
		curveIndices.push_back(i);
	}
	curve->set_triangles(curveIndices);

	// We now call refreshLines to fill up the vertex data
	refreshLines();
}