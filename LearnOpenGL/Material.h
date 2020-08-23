#pragma once
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Material
{
public:
	Material(Shader* _shader, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _shininess);
	~Material();

public: void SetTexure(GLuint _diffuse, GLuint _specular);

public:
	Shader* shader;
	//基础颜色（最案部分）
	glm::vec3 ambient;
	//漫反射
	glm::vec3 diffuse;
	//镜面反射
	glm::vec3 specular;
	//粗糙度 越大越光滑
	float shininess;

	GLuint diffuseTexure;
	GLuint specularTexure;
};

