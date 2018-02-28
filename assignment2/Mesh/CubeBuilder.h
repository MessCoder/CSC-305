#ifndef CUBE_BUILDER_H
#define CUBE_BUILDER_H

#include "../common.h"
#include "MeshBuilder.h"

class CubeBuilder : public MeshBuilder {
protected: 
	virtual void _build() override;
};

#endif // !CUBE_BUILDER_H