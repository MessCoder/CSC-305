/*
 * CSC 305 201801 UVIC
 * The purpose of this source file is to demonstrate the Mesh class which you may use in assignment 2
 * Its only functionality is to render vertices/normals/textures and load textures from png files
 * A demonstration of an ImGui menu window is also included in this file
*/
#include "Mesh/Mesh.h"
#include "Mesh/CubeBuilder.h"
#include "Mesh/CylinderBuilder.h"
#include "Mesh/SphereBuilder.h"
#include "objFile.h"

#include "OpenGP/GL/glfw_helpers.h"

#include <OpenGP/types.h>
#include <OpenGP/MLogger.h>
#include <OpenGP/GL/Application.h>
#include <OpenGP/GL/ImguiRenderer.h>

using namespace OpenGP;

bool stateStable = false;
Mesh renderMesh;
Mat4x4 model;

void applyTransformation(Mat4x4 transformation) {
	stateStable = false;
	model = transformation * model;
	stateStable = true;
}

void buildPlane(Mesh& renderMesh) {

	renderMesh.init();

	/// Load Vertices and Indices (minimum required for Mesh::draw to work)
	std::vector<Vec3> vertList;
	vertList.push_back(Vec3(0, 0, 0));
	vertList.push_back(Vec3(1, 0, 0));
	vertList.push_back(Vec3(1, 1, 0));
	vertList.push_back(Vec3(0, 1, 0));
	std::vector<unsigned int> indexList;
	indexList.push_back(0); // Face 1
	indexList.push_back(1);
	indexList.push_back(2);
	indexList.push_back(2); // Face 2
	indexList.push_back(3);
	indexList.push_back(0);
	renderMesh.loadVertices(vertList, indexList);

	/// Load normals
	std::vector<Vec3> normList;
	normList.push_back(Vec3(0, 0, 1));
	normList.push_back(Vec3(0, 0, 1));
	normList.push_back(Vec3(0, 0, 1));
	normList.push_back(Vec3(0, 0, 1));
	renderMesh.loadNormals(normList);

	/// Load textures (assumes texcoords)
	renderMesh.loadTextures("earth.png");

	/// Load texture coordinates (assumes textures)
	std::vector<Vec2> tCoordList;
	tCoordList.push_back(Vec2(0, 0));
	tCoordList.push_back(Vec2(1, 0));
	tCoordList.push_back(Vec2(1, 1));
	tCoordList.push_back(Vec2(0, 1));
	renderMesh.loadTexCoords(tCoordList);
}

int main() {

    Application app;
    ImguiRenderer imrenderer;
    
	// Build and export a mesh
	Mesh exportMesh;
	
	SphereBuilder(100, 100).build(exportMesh);

	ObjFile().setMesh(exportMesh).save("output.obj");

	// Load the mesh to show
	renderMesh = ObjFile().load("output.obj").mesh;
	
	// Set the texture to show
	renderMesh.loadTextures("earth.png");

	Mat4x4 modelTransform = Mat4x4::Identity();
	model = modelTransform.matrix();

	stateStable = true;

	// Save the mesh into a file

    /// Create main window, set callback function
    auto &window1 = app.create_window([&](Window &window){
        int width, height;
        std::tie(width, height) = window.get_size();

        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glClearColor(0.0f, 0.0f, 0.0f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /// Wireframe rendering, might be helpful when debugging your mesh generation
        //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		float ratio = width / (float)height;
        Mat4x4 projection = OpenGP::perspective(70.0f, ratio, 0.1f, 10.0f);

        //camera movement
        float time = .5f * (float)glfwGetTime();
        Vec3 cam_pos(2*cos(time), 2.0, 2*sin(time));
        Vec3 cam_look(0.0f, 0.0f, 0.0f);
        Vec3 cam_up(0.0f, 1.0f, 0.0f);
        Mat4x4 view = OpenGP::lookAt(cam_pos, cam_look, cam_up);

		if (stateStable) {
			renderMesh.draw(model, view, projection);
		}
    });
    window1.set_title("Assignment 2");

    /// Create window for IMGUI, set callback function
	auto &window2 = app.create_window([&](Window &window) {
		int width, height;
		std::tie(width, height) = window.get_size();

		imrenderer.begin_frame(width, height);

		ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Open obj.", "Ctrl+O")) {

			}
			if (ImGui::MenuItem("Save obj.", "Ctrl+S")) {

			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Create")) {
			if (ImGui::MenuItem("Create cube", "Ctrl+1")) {

			}
			if (ImGui::MenuItem("Create cylinder", "Ctrl+2")) {

			}
			if (ImGui::MenuItem("Create sphere", "Ctrl+3")) {

			}
			ImGui::EndMenu();
		}
        ImGui::EndMainMenuBar();

		
		ImGui::SetNextWindowSize(ImVec2(300, 200));
        ImGui::Begin("Transformations");

		ImGui::Text("Rotate:");

		static float rotation[] = { .0, .0, .0 };
		ImGui::InputFloat3("", rotation);
		ImGui::SameLine();
		if (ImGui::Button("Apply")) {

		}

        ImGui::Text("Translate:");
		
		static float translation[] = { .0, .0, .0 };
		ImGui::InputFloat3("", translation);
		ImGui::SameLine();
		if (ImGui::Button("Apply")) {

			Mat4x4 translationMatrix;
			translationMatrix <<
				1., 0., 0., translation[0],
				0., 1., 0., translation[1],
				0., 0., 1., translation[2],
				0., 0., 0., 1.;

			applyTransformation(translationMatrix);
			translation[0] = translation[1] = translation[2] = 0.;
		}

		ImGui::Text("Scale:");

		static float scaling[] = { .0, .0, .0 };
		ImGui::InputFloat3("", scaling);
		ImGui::SameLine();
		if (ImGui::Button("Apply")) {

			Mat4x4 scalingMatrix;
			scalingMatrix <<
				scaling[0], 0., 0., 1.,
				0., scaling[1], 0., 1.,
				0., 0., scaling[2], 1.,
				0., 0., 0., 1.;

			applyTransformation(scalingMatrix);
			scaling[0] = scaling[1] = scaling[2] = 0.;
		}

        ImGui::End();

        glClearColor(0.15f, 0.15f, 0.15f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        imrenderer.end_frame();
    });
    window2.set_title("imgui Test");

    return app.run();
}
