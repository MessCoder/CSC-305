
#include "objFile.h"
#include <fstream>
#include <iostream>
#include <sstream>

void addVertex(std::string line, std::stringstream& input, std::vector<Vec3>& vertexArray);
void addNormal(std::string line, std::stringstream& input, std::vector<Vec3>& normalArray);
void addTextCoords(std::string line, std::stringstream& input, std::vector<Vec2>& tCoordsArray);
void addIndexes(std::string line, std::stringstream& input, std::vector<unsigned int>& indexArray);

ObjFile& ObjFile::setMesh(Mesh mesh) {
	this->mesh = mesh;
	return *this;
}

ObjFile& ObjFile::save(std::string path) {

	std::ofstream obj;
	obj.open(path);

	auto vertexArray = mesh.getVertexArray();
	auto indexArray = mesh.getIndexArray();
	auto normalArray = mesh.getNormalArray();
	auto tCoordsArray = mesh.getTCoordArray();

	for (int i = 0; i < vertexArray.size(); i++) {
		Vec3 v = vertexArray[i];
		obj << "v " << v.x() << " " << v.y() << " " << v.z() << std::endl;
	}

	for (int i = 0; i < tCoordsArray.size(); i++) {
		Vec2 vt = tCoordsArray[i];
		obj << "vt " << vt.x() << " " << vt.y() << std::endl;
	}

	for (int i = 0; i < normalArray.size(); i++) {
		Vec3 vn = normalArray[i];
		obj << "vn " << vn.x() << " " << vn.y() << " " << vn.z() << std::endl;
	}

	for (int i = 0; i + 2 < indexArray.size(); i += 3) {
		obj << "f " << indexArray[i] + 1 << " " 
			<< indexArray[i + 1] + 1 << " " 
			<< indexArray[i + 2] + 1 << std::endl;
	}

	return *this;
}

ObjFile& ObjFile::load(std::string path) {

	std::vector<Vec3> vertexArray;
	std::vector<unsigned int> indexArray;
	std::vector<Vec3> normalArray;
	std::vector<Vec2> tCoordsArray;

	std::ifstream obj;
	
	obj.open(path);

	if (!obj.is_open()) {
		std::cerr << "Failed to open mesh file; " << strerror(errno);
	}

	std::string line = "";
	std::string lineType = "";

	// Process all lines in the file 
	while (std::getline(obj, line)) {

		// For each line try to get the type of element
		std::stringstream lineStream(line);
		std::getline(lineStream, lineType, ' ');

		if (lineType.compare("v") == 0) {
			addVertex(line, lineStream, vertexArray);
		}
		else if (lineType.compare("vt") == 0) {
			addTextCoords(line, lineStream, tCoordsArray);
		}
		else if (lineType.compare("vn") == 0) {
			addNormal(line, lineStream, normalArray);
		}
		else if (lineType.compare("f") == 0) {
			addIndexes(line, lineStream, indexArray);
		}
		else if (lineType.length() != 0 && lineType[0] == '#') {
			// It's a comment, ignore
		}
		else {
			std::cerr << "Unrecognised line: " << line;
		}
	}

	mesh.init();
	mesh.loadVertices(vertexArray, indexArray);
	mesh.loadNormals(normalArray);
	mesh.loadTexCoords(tCoordsArray);

	return *this;
}

void addVertex(std::string line, std::stringstream& input, std::vector<Vec3>& vertexArray) {
	float x, y, z;

	if (input >> x && input >> y && input >> z) {

		vertexArray.push_back(Vec3(x, y, z));
	}
	else {
		std::cerr << "Can't parse 3 floating point coordinates in vertex; " 
			<< line << std::endl;

		vertexArray.push_back(Vec3(0, 0, 0));
	}
}

void addNormal(std::string line, std::stringstream& input, std::vector<Vec3>& normalArray) {
	float x, y, z;

	if (input >> x && input >> y && input >> z) {
		normalArray.push_back(Vec3(x, y, z));
	}
	else {
		std::cerr << "Can't parse 3 floating point components in normal; "
			<< line << std::endl;

		normalArray.push_back(Vec3(x, y, z));
	}
}

void addTextCoords(std::string line, std::stringstream& input, std::vector<Vec2>& tCoordsArray) {
	float u, v;

	if (input >> u && input >> v) {
		tCoordsArray.push_back(Vec2(u, v));
	}
	else {
		std::cerr << "Can't parse 2 floating point coordinates in UV; "
			<< line << std::endl;

		tCoordsArray.push_back(Vec2(0, 0));
	}
}

void addIndexes(std::string line, std::stringstream& input, std::vector<unsigned int>& indexArray) {
	unsigned int a, b, c;

	if (input >> a && input >> b && input >> c) {
		indexArray.push_back(a - 1);
		indexArray.push_back(b - 1);
		indexArray.push_back(c - 1);
	}
	else {
		std::cerr << "Can't parse 3 unsigned int indexes of vertices in face; "
			<< line << std::endl;
	}
}