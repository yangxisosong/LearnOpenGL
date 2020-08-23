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
	//������ɫ������֣�
	glm::vec3 ambient;
	//������
	glm::vec3 diffuse;
	//���淴��
	glm::vec3 specular;
	//�ֲڶ� Խ��Խ�⻬
	float shininess;

	GLuint diffuseTexure;
	GLuint specularTexure;
};

