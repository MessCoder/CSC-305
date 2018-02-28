#ifndef MESH_H
#define MESH_H

#include "OpenGP/Image/Image.h"
#include "OpenGP/GL/Eigen.h"

class Mesh{
protected:
    GLuint _vao; ///< vertex array object
    GLuint _pid; ///< GLSL shader program ID
    GLuint _texture;    ///< Texture buffer
    GLuint _vpoint;    ///< vertices buffer
    GLuint _vnormal;   ///< normals buffer
    GLuint _tcoord;    ///< texture coordinates buffer

    unsigned int numVertices;

    bool hasNormals;
    bool hasTextures;
    bool hasTexCoords;

	std::vector<OpenGP::Vec3> vertexArray;
	std::vector<unsigned int> indexArray;
	std::vector<OpenGP::Vec3> normalArray;
	std::vector<OpenGP::Vec2> tCoordArray;

public:

	GLuint getProgramID();
	
	void init(); // This initializes shaders too
	void loadVertices(const std::vector<OpenGP::Vec3> &vertexArray, const std::vector<unsigned int> &indexArray);
	void loadNormals(const std::vector<OpenGP::Vec3> &normalArray);
	void loadTexCoords(const std::vector<OpenGP::Vec2> &tCoordArray); // Assumes texture
	void loadTextures(const std::string filename); // Assumes texture mapping
	void draw(OpenGP::Mat4x4 Model, OpenGP::Mat4x4 View, OpenGP::Mat4x4 Projection);

	std::vector<OpenGP::Vec3> getVertexArray();
	std::vector<unsigned int> getIndexArray();
	std::vector<OpenGP::Vec3> getNormalArray();
	std::vector<OpenGP::Vec2> getTCoordArray();
};

#endif // !MESH_H