#include "Camera.h"

namespace Voxels {
	Camera::Camera() : fov(glm::radians(45.f)), near(0.1f),
						far(1000.f), width(500.f), height(500.f),
						position(0, 0, 5), direction(0, 0, -1),
						model(1), projection(1), view(1) 
	{
	}
	
	Camera::Camera(glm::vec3 pos, glm::vec3 dir, float fov, float near, float far, float width, float height) :
				fov(fov), near(near), far(far), width(width), height(height),
				pitch(0), yaw(PI/-2.f), position(pos), direction(dir),
				model(1), projection(1), view(1)
	{
	}

	Camera::Camera(glm::vec3 pos, float pitch, float yaw, float fov, float near, float far, float width, float height) :
			fov(fov), near(near), far(far), width(width), height(height),
			pitch(pitch), yaw(yaw), position(pos), direction(glm::vec3(glm::cos(yaw), 1., glm::sin(yaw))*glm::vec3(glm::cos(pitch), glm::sin(pitch), glm::cos(pitch))),
			model(1), projection(1), view(1)
	{
	}

	Camera::~Camera() {}
	
	void Camera::init() {
		view = glm::lookAt(position, position + direction, glm::vec3(0., 1., 0.));
		projection = glm::perspective(fov, width / height, near, far);
		mvp = projection * view * model;
	}

	void Camera::setPosition(glm::vec3 pos) {
		position = pos;
		updateView();
	}
	
	glm::vec3 Camera::getPosition() {
		return position;
	}
	
	GLfloat *Camera::getPositionPtr() {
		return glm::value_ptr(position);
	}

	void Camera::setDirection(glm::vec3 dir) {
		direction = dir;
		updateView();
	}
	
	glm::vec3 Camera::getDirection() {
		return glm::normalize(direction);
	}
	
	glm::mat4 Camera::getMVP() {
		return mvp;
	}

	const GLfloat *Camera::getMVPPtr() {
		return glm::value_ptr(mvp);
	}
	
	const GLfloat *Camera::getInverseProjectionPtr() {
		return glm::value_ptr(glm::inverse(projection));
	}

	void Camera::update() {
		mvp = projection * view * model;
		cameraUpdated = true;
	}

	void Camera::updateView() {
		view = glm::lookAt(position, position + direction, glm::vec3(0., 1., 0.));
		update();
	}

	void Camera::updateProjection() {
		projection = glm::perspective(fov, width / height, near, far);
		update();
	}

	bool Camera::getCameraUpdated() {
		return cameraUpdated;
	}

	void Camera::setCameraUpdated() {
		cameraUpdated = false;
	}

	glm::vec3 Camera::getRight() {
		return glm::normalize(glm::cross(getDirection(), glm::vec3(0., 1., 0.)));
	}

	glm::vec3 Camera::getUp() {
		return glm::cross(getRight(), getDirection());
	}

	float Camera::getYaw() {
		return yaw;
	}

	void Camera::setYaw(float yaw) {
		this->yaw = yaw;
		setDirection(glm::normalize(glm::vec3(glm::cos(yaw), 1., glm::sin(yaw))*
			glm::vec3(glm::cos(pitch), glm::sin(pitch), glm::cos(pitch))));
	}

	float Camera::getPitch() {
		return pitch;
	}

	void Camera::setPitch(float pitch) {
		if (pitch > 89) {
			pitch = 89;
		}
		if (pitch < -89) {
			pitch = -89;
		}
		this->pitch = pitch;
		setDirection(glm::normalize(glm::vec3(glm::cos(yaw), 1., glm::sin(yaw))*
			glm::vec3(glm::cos(pitch), glm::sin(pitch), glm::cos(pitch))));
	}
}