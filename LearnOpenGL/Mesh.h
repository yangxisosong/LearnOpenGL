#pragma once
#include <glm/glm.hpp>
#include <string>
#include<vector>
#include "Shader.h"
#include <glad/glad.h>

//顶点数据
struct Vertex 
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCorrds;

};
//纹理
struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};


class Mesh
{
public:
	Mesh(float vertices[]);
	Mesh(std::vector<Vertex> victices, std::vector<unsigned int> indices, std::vector<Texture> textures);

public:
	//网格数据
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	void Draw(Shader* shader);

private: 
	GLuint VBO, VAO, EBO;
	void SetUpMesh();
};

