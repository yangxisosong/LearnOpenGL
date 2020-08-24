#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light
{

public:
	Light();
	~Light();

public:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 angles;
	glm::vec3 direction = glm::vec3(0, 0, 1);

public:
	void UpdateDirection() 
	{
		direction = glm::vec3(0, 0, 1.0f);
		direction = glm::rotateZ(direction, angles.z);
		direction = glm::rotateX(direction, angles.x);
		direction = glm::rotateY(direction, angles.y);
		direction = -1.0f * direction;
	}
};

class ParallelLight:public Light
{
public:
	ParallelLight(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~ParallelLight();
};

class PointLight:public Light
{
public:
	PointLight(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~PointLight();

public:
	float constant;
	float linear;
	float quadratic;

private:

};