#pragma once
#include <glm/glm.hpp>
#include <string>
#include<vector>
#include "Shader.h"
#include <glad/glad.h>

//float verticesaa[] = {
// 0.5f,  0.5f, 0.0f,  // top right
// 0.5f, -0.5f, 0.0f,  // bottom right
//-0.5f, -0.5f, 0.0f,  // bottom left
//-0.5f,  0.5f, 0.0f   // top left 
//};
//unsigned int indicesaa[] = {  // note that we start from 0!
//	0, 1, 3,  // first Triangle
//	1, 2, 3   // second Triangle
//};
//顶点数据
struct Vertex 
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;

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
	Mesh(std::vector<float> v, std::vector<int> i);

public:
	//网格数据
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> verticesFloat;
	std::vector<int> indicesFloat;
	std::vector<Texture> textures;

	void Draw(Shader* shader);

private: 
	GLuint VBO, VAO, EBO;
	void SetUpMesh();
	void SetUpMesh2();
	void SetUpMeshFromArry();
	float verticesh[12] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indicesh[6] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

};

