#ifndef OBJ_FILE_H
#define OBJ_FILE_H

#include "common.h"
#include "Mesh\Mesh.h"

class ObjFile {
public:	
	// Mesh to save or mesh readed from a given file.
	Mesh mesh;

	// Cascade setter
	ObjFile& setMesh(Mesh mesh);

	// Saves the current mesh and texture to an obj file.
	ObjFile& save(std::string path);

	// Loads the obj file at the given path, allowing to get
	// it's mesh.
	ObjFile& load(std::string path);
};

#endif // !OBJ_FILE_H