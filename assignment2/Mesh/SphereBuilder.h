#ifndef SPHERE_BUILDER_H
#define SPHERE_BUILDER_H

#include "MeshBuilder.h"

class SphereBuilder : public MeshBuilder {
public:
	SphereBuilder(unsigned int hResolution, unsigned int vResolution);
	virtual void _build() override;

private:
	unsigned int hResolution;
	unsigned int vResolution;
	Eigen::Matrix3f hRotation;
	Eigen::Matrix3f vRotation;

	// Assume spherical texture mapping and 
	// normal equal to the vertex position.
	void addVertexS(Vec3 pos);

	void buildVertices();
	void buildTris();
};

#endif // !SPHERE_BUILDER_H
