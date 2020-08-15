#include "Camera.h"

Camera::Camera()
{
	//相机位置
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	//相机 前向
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	//相机 上方向
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	cameraRight = glm::normalize(glm::cross(this->cameraFront, this->WorldUp));

	WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

}

// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(this->cameraPos, this->cameraPos + this->cameraFront, this->cameraUp);
}

void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
	GLfloat velocity = MovementSpeed * deltaTime;
	if (direction == Camera_Movement::FORWARD)
		this->cameraPos += this->cameraFront * velocity;
	if (direction == Camera_Movement::BACKWARD)
		this->cameraPos -= this->cameraFront * velocity;
	if (direction == Camera_Movement::LEFT)
		this->cameraPos -= this->cameraRight * velocity;
	if (direction == Camera_Movement::RIGHT)
		this->cameraPos += this->cameraRight * velocity;
}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
	xoffset *= this->MouseSensitivit;
	yoffset *= this->MouseSensitivit;

	this->Yaw += xoffset;
	this->Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (this->Pitch > 89.0f)
			this->Pitch = 89.0f;
		if (this->Pitch < -89.0f)
			this->Pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	this->updateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yoffset)
{
	/*if (this->Zoom >= 1.0f && this->Zoom <= 45.0f)
		this->Zoom -= yoffset;
	if (this->Zoom <= 1.0f)
		this->Zoom = 1.0f;
	if (this->Zoom >= 45.0f)
		this->Zoom = 45.0f;*/
	this->cameraPos += this->cameraFront * yoffset*0.1f;
}

void Camera::updateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
	front.y = sin(glm::radians(this->Pitch));
	front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
	this->cameraFront = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	this->cameraRight = glm::normalize(glm::cross(this->cameraFront, this->WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	this->cameraUp = glm::normalize(glm::cross(this->cameraRight, this->cameraFront));
}

