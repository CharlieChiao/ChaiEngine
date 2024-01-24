#include "Mesh.h"

Mesh::Mesh(vector<Vertex>& vertices, vector<GLuint>& indices, vector<Texture>& textures)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	vao.Bind();

	VBO vbo(vertices);
	EBO ebo(indices);

	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	vao.LinkAttrib(vbo, 4, 3, GL_FLOAT, sizeof(Vertex), (void*)(11 * sizeof(float)));
	vao.LinkAttrib(vbo, 5, 3, GL_FLOAT, sizeof(Vertex), (void*)(14 * sizeof(float)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}

Mesh::Mesh(vector<Vertex>& vertices, vector<GLuint>& indices)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;

	vao.Bind();

	VBO vbo(vertices);
	EBO ebo(indices);

	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}

void Mesh::Draw(Shader& shader, Camera& camera)
{
	// Bind shader to be able to access uniforms
	shader.Activate();
	vao.Bind();

	// Keep track of how many of each type of textures we have
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;
	unsigned int numNormal = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		string num;
		string type = textures[i].type;
		if (type == "diffuse")
		{
			num = to_string(numDiffuse++);
		}
		else if (type == "specular")
		{
			num = to_string(numSpecular++);
		}
		else if (type == "normal")
		{
			num = to_string(numNormal++);
		}
		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}

	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "cameraMatrix");
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
