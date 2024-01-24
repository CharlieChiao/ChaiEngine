#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

using namespace glm;
using namespace std;

class EBO
{
public:

	GLuint ID;

	EBO(vector <GLuint>& indices);

	void Bind();

	void Unbind();

	void Delete();
};

#endif