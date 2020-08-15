#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// GL Includes
#include <GL/glew.h>

//��������ƶ����ֿ��ܵ�ѡ����Ϊ����Ĵ���ϵͳ�ض������뷨�߾���
enum class Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat ROLL = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;

class Camera
{
public: Camera();

public:
	glm::mat4 GetViewMatrix();
	//��������
	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
	//������
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);

	void ProcessMouseScroll(GLfloat yoffset);
public:
	//���λ��
	glm::vec3 cameraPos;
	//��� ǰ��
	glm::vec3 cameraFront;
	//��� �Ϸ���
	glm::vec3 cameraUp;

	glm::vec3 cameraRight;

	// Eular Angles
	GLfloat Yaw = YAW;
	GLfloat Pitch = PITCH;
	GLfloat Roll = ROLL;
	// Camera options
	GLfloat MovementSpeed = 1.0f;
	GLfloat MouseSensitivit = SENSITIVTY;
	GLfloat Zoom = ZOOM;

	glm::vec3 WorldUp;

private: 
	void updateCameraVectors();
};

