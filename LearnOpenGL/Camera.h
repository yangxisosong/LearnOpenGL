#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// GL Includes
#include <GL/glew.h>

//定义相机移动几种可能的选择。作为抽象的窗口系统特定的输入法走就走
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
	//按键控制
	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
	//鼠标控制
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);

	void ProcessMouseScroll(GLfloat yoffset);
public:
	//相机位置
	glm::vec3 cameraPos;
	//相机 前向
	glm::vec3 cameraFront;
	//相机 上方向
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

