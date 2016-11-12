#include "Light.h"


namespace Voxels {
	Light::Light(glm::vec3 pos) : position(pos), direction(0.),
								  projection(glm::ortho(-10., 10., -10., 10., 1., 7.5)),
								  view(glm::lookAt(position, position + direction, glm::vec3(0., 1., 0.))), VP(projection * view)
	{}

	Light::~Light() {}

	glm::vec3 Light::getPosition() {
		return position;
	}

	GLfloat *Light::getPositionPtr() {
		return glm::value_ptr(position);
	}

	void Light::setPosition(glm::vec3 pos) {
		position = pos;
		updateView();
	}

	glm::vec3 Light::getDirection() {
		return direction;
	}
	
	void Light::setDirection(glm::vec3 dir) {
		direction = dir;
		updateView();
	}
	
	glm::mat4 Light::getVP() {
		return VP;
	}
	
	GLfloat *Light::getVPPtr() {
		return glm::value_ptr(VP);
	}

	void Light::updateView() {
		view = glm::lookAt(position, position + direction, glm::vec3(0., 1., 0.));
		VP = projection * view;
	}
}
