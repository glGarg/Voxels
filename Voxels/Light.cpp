#include "Light.h"


namespace Voxels {
	Light::Light(glm::vec3 pos) : position(pos) {}

	Light::~Light() {}

	glm::vec3 Light::getPosition() {
		return position;
	}

	GLfloat *Light::getPositionPtr() {
		return glm::value_ptr(position);
	}

	void Light::setPosition(glm::vec3 pos) {
		position = pos;
	}
}
