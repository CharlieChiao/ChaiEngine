#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>
#include "VAO.h"
#include "EBO.h"
#include "Engine/Source/Camera/Public/Camera.h"
#include "Texture.h"

using namespace std;

class Mesh 
{
public:
	vector <Vertex> vertices;
	vector <GLuint> indices;
	vector <Texture> textures;

	VAO vao;

	Mesh(vector <Vertex>& vertices, vector <GLuint>& indices, vector <Texture>& textures);
	Mesh(vector <Vertex>& vertices, vector <GLuint>& indices);

	void Draw(Shader& shader, Camera& camera);
};

#endif
