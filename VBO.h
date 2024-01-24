#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

using namespace glm;
using namespace std;

struct Vertex 
{
	vec3 position;
	vec3 color;
	vec3 normal;
	vec2 UvCord;
	vec3 tangent;
	vec3 bitangent;
};

class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(vector<Vertex>& vertices);

	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();
};

#endif
