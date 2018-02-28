#ifndef CYLINDER_BUILDER_H
#define CYLINDER_BUILDER_H

#include "MeshBuilder.h"

class CylinderBuilder : public MeshBuilder {
public:
	CylinderBuilder(unsigned int circunferenceResolution);
protected:
	virtual void _build() override;
	
	// Assumes cylindrical texture mapping
	void addVertexCuv(Vec3 pos, Vec3 normal);

	// Adds two pairs of vertices to the circunference
	// of the cylinder
	void addAxisPair(Vec3 center);

private:
	unsigned int circunferenceResolution;
	
	// Rotation between vertices in a circunference
	Eigen::Matrix3f rotation;
};

#endif // !CYLINDER_BUILDER_H