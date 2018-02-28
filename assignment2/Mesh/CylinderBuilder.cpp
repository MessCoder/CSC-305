
#include "CylinderBuilder.h"
#include <math.h>

CylinderBuilder::CylinderBuilder(unsigned int circunferenceResolution) {
	this->circunferenceResolution = circunferenceResolution;
	
	this->rotation = Eigen::AngleAxisf(
		2 * M_PI / circunferenceResolution,
		Vec3(0, 1, 0)
	).toRotationMatrix();
}

void CylinderBuilder::_build() {

	// Add central axis
	addVertexCuv(Vec3(0, -1, 0), Vec3(0, -1, 0));
	addVertexCuv(Vec3(0, 1, 0), Vec3(0, 1, 0));

	// Center of the current step in the revolution
	// of axis composing the cylinder
	// It's important for this to be at the atan2(z, x) discontinuity.
	Vec3 revolutionCenter = Vec3(0, 0, -1);
	
	// Add first pair of external axises
	addAxisPair(revolutionCenter);
	
	// c = count of vertices fully incorporated to the circunference
	for (int i = 0, c = 0; i < circunferenceResolution; i++, c+=4) {
		
		// Add new pair of external axises
		revolutionCenter = rotation * revolutionCenter;
		addAxisPair(revolutionCenter);

		// Make top and bottom triangles between the center 
		// axis, the previous internal revolved axis
		// and the new one.
		makeTri(
			0, // Bottom central vertex
			6 + c, // 6 = 2nd axis pair bottom internal vertex 
			2 + c // 2 = 1st axis pair bottom internal vertex
		);
		makeTri(
			1, // Top central vertex
			3 + c, // 3 = 1st axis pair top internal vertex
			7 + c // 7 = 2nd axis pair top internal vertex 
		);
		
		// Make external face between the last external axis
		// and the previous one.
		makeQuad(
			8 + c, // Bottom vertex in last external axis
			4 + c, // Bottom vertex in previous external axis
			9 + c, // Top vertex in last external axis
			5 + c // Top vertex in previous external axis
		);
	}

	// The x coordinate in the cylindrical uv mapping misbehaves
	// on the vecinity of the atan(z, x) discontinuity, so we have to
	// hardcode the uv coordinates for the first and last axis pairs.

	// First axis pair
	textCoords[2] = textCoords[4] = Vec2(0, 0); // Bottom vertices
	textCoords[3] = textCoords[5] = Vec2(0, 1); // Top vertices

	// Last axis pair
	int c = (circunferenceResolution - 1) * 4;
	textCoords[c + 6] = textCoords[c + 8] = Vec2(1, 0); // Bottom vertices
	textCoords[c + 7] = textCoords[c + 9] = Vec2(1, 1); // Top vertices
}

void CylinderBuilder::addVertexCuv(Vec3 pos, Vec3 normal) {

	// We use the angle of the position vector on the xz plane
	// as the texture space x coordinate
	float u = atan2(pos.x(), pos.z()) / (2 * M_PI) + 0.5;

	// We use the y position of the vertex (bound between -1 and 1)
	// as the texture space y coordinate
	float v = pos.y() / 2 + 0.5;

	addVertex(pos, normal, Vec2(u, v));
}

void CylinderBuilder::addAxisPair(Vec3 center) {
	Vec3 up = Vec3(0, 1, 0);

	// 1st Axis for the bottom and top faces (internal)
	addVertexCuv(center - up, -up);
	addVertexCuv(center + up, up);

	// 2nd Axis for the external faces (external)
	// assuming center is normalized
	addVertexCuv(center - up, center);
	addVertexCuv(center + up, center);
}