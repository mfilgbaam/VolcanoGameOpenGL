#include "camera.h"

Camera::Camera(glm::vec3 cameraPosition)
{
	this->cameraPosition = cameraPosition;
	this->cameraViewDirection = glm::vec3(-1.0f, 0.0f, 0.0f);
	this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->cameraRight = glm::cross(cameraViewDirection, cameraUp);
	this->rotationOx = 0.0f;
	this->rotationOy = -90.0f;
}

Camera::Camera()
{
	this->cameraPosition = glm::vec3(0.0f, 0.0f, 10.0f);
	this->cameraViewDirection = glm::vec3(0.0f, 0.0f, 1.0f);
	this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->cameraRight = glm::cross(cameraViewDirection, cameraUp);
	this->rotationOx = 0.0f;
	this->rotationOy = -90.0f;
}

Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraViewDirection, glm::vec3 cameraUp)
{
	this->cameraPosition = cameraPosition;
	this->cameraViewDirection = cameraViewDirection;
	this->cameraUp = cameraUp;
	this->cameraRight = glm::cross(cameraViewDirection, cameraUp);
}

Camera::~Camera()
{
}

void Camera::keyboardMoveFront(float cameraSpeed)
{
	cameraPosition += cameraViewDirection * glm::vec3(1.0f, 0.0f, 1.0f) * cameraSpeed;
}

void Camera::keyboardMoveBack(float cameraSpeed)
{
	cameraPosition -= cameraViewDirection * glm::vec3(1.0f, 0.0f, 1.0f) * cameraSpeed;
}

void Camera::keyboardMoveLeft(float cameraSpeed)
{
	cameraPosition -= glm::normalize(glm::cross(cameraViewDirection, cameraUp)) * glm::vec3(1.0f, 0.0f, 1.0f) * cameraSpeed;
}

void Camera::keyboardMoveRight(float cameraSpeed)
{
	cameraPosition += glm::normalize(glm::cross(cameraViewDirection, cameraUp)) * glm::vec3(1.0f, 0.0f, 1.0f) * cameraSpeed;
}

glm::vec3 Camera::TestMoveFront(float cameraSpeed)
{
	return cameraPosition + cameraViewDirection * glm::vec3(1.0f, 0.0f, 1.0f) * cameraSpeed;
}

glm::vec3 Camera::TestMoveBack(float cameraSpeed)
{
	return cameraPosition - cameraViewDirection * glm::vec3(1.0f, 0.0f, 1.0f) * cameraSpeed;
}

glm::vec3 Camera::TestMoveLeft(float cameraSpeed)
{
	return cameraPosition - glm::normalize(glm::cross(cameraViewDirection, cameraUp)) * glm::vec3(1.0f, 0.0f, 1.0f) * cameraSpeed;
}

glm::vec3 Camera::TestMoveRight(float cameraSpeed)
{
	return cameraPosition + glm::normalize(glm::cross(cameraViewDirection, cameraUp)) * glm::vec3(1.0f, 0.0f, 1.0f) * cameraSpeed;
}

void Camera::keyboardMoveUp(float cameraSpeed)
{
	cameraPosition += cameraUp * cameraSpeed;
}

void Camera::keyboardMoveDown(float cameraSpeed)
{
	cameraPosition -= cameraUp * cameraSpeed;
}

void Camera::rotateOx(float angle)
{
	if ((angle > 0 && cameraViewDirection.y < 0.9f) || (angle < 0 && cameraViewDirection.y > -0.9f)) {

		cameraViewDirection = glm::normalize(glm::vec3((glm::rotate(glm::mat4(1.0f), angle, cameraRight) * glm::vec4(cameraViewDirection, 1))));
		cameraUp = glm::normalize(glm::cross(cameraRight, cameraViewDirection));
		cameraRight = glm::cross(cameraViewDirection, cameraUp);
		cameraRight.y = 0;
	}
}

void Camera::rotateOy(float angle)
{
	float temp = cameraViewDirection.y;
	cameraViewDirection = glm::normalize(glm::vec3((glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(cameraViewDirection, 1))));
	cameraViewDirection.y = temp;
	cameraRight = glm::normalize(glm::vec3((glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(cameraRight, 1))));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraViewDirection));

}


glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(cameraPosition, cameraPosition + cameraViewDirection, cameraUp);
}

glm::vec3 Camera::getCameraPosition()
{
	return cameraPosition;
}

glm::vec3 Camera::getCameraViewDirection()
{
	return cameraViewDirection;
}

glm::vec3 Camera::getCameraUp()
{
	return cameraUp;
}


