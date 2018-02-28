
#include "SphereBuilder.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define ROWSIZE (this->hResolution + 1)

SphereBuilder::SphereBuilder(unsigned int hResolution, unsigned int vResolution) {

	this->hResolution = hResolution;
	this->vResolution = vResolution;

	this->hRotation = Eigen::AngleAxisf(
		2 * M_PI / hResolution,
		Vec3(0, 1, 0)
	).toRotationMatrix();

	this->vRotation = Eigen::AngleAxisf(
		M_PI / (vResolution - 1),
		Vec3(0, 0, -1)
	).toRotationMatrix();
}

void SphereBuilder::_build() {

	buildVertices();
	buildTris();
}

void SphereBuilder::buildVertices() {

	// Bottom vertex
	Vec3 rowStart(0, -1, 0);
	addVertexS(rowStart); 

	// All vertices in intermediate rows
	for (unsigned int row = 1; row < vResolution - 1; row++) {

		rowStart = vRotation * rowStart;

		Vec3 pos = rowStart;
		
		for (unsigned int column = 0; column < hResolution + 1; column++) {

			addVertexS(pos);
			pos = hRotation * pos;
		}

		// In order to tile the whole texture from x = 0 to x = 1, we
		// duplicate the column at the atan2(z, x) discontinuity and
		// harcode it's x coordinates.
		int rowStartIndex = (row - 1) * ROWSIZE + 1;
		textCoords[rowStartIndex] = Vec2(
			0,
			textCoords[rowStartIndex].y()
		);

		int rowEndIndex = row * ROWSIZE;
		textCoords[rowEndIndex] = Vec2(
			1,
			textCoords[rowEndIndex].y()
		);
	}

	// Top vertex
	addVertexS(Vec3(0, 1, 0));
}

void SphereBuilder::buildTris() {
	
	// Bottom strip
	for (unsigned int i = 0; i < ROWSIZE; i++) {
		makeTri(0, i, i + 1);
	}

	// Top strip
	// start and ending of the last <b>row</b>
	int start = 1 + ROWSIZE * (vResolution - 3);
	int end = ROWSIZE * (vResolution - 2);

	for (int i = start; i < end; i++) {
		makeTri(end + 1, i + 1, i);
	}

	// Intermediate strips
	for (unsigned int row = 1; row < vResolution - 2; row++) {
		int start = (row - 1) * ROWSIZE + 1;
		int end = row * ROWSIZE;

		// rest of the strip
		for (int i = start; i < end; i++) {
			makeQuad(
				i, // Current row
				i + 1,
				i + ROWSIZE, // Next row
				i + 1 + ROWSIZE
			);
		}
	}

}

void SphereBuilder::addVertexS(Vec3 pos) {

	float u = 0.5 - atan2(pos.z(), pos.x()) / (2 * M_PI);
	float v = asin(pos.y()) / M_PI + 0.5;

	addVertex(pos, pos, Vec2(u, v));
}