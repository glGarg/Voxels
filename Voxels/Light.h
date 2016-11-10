#pragma once
#include <glm.hpp>
#include <gl/glew.h>
#include <gtc/type_ptr.hpp>

namespace Voxels {
	class Light {
	public:
		Light(glm::vec3 pos);
		~Light();
		glm::vec3 getPosition();
		GLfloat *getPositionPtr();
		void setPosition(glm::vec3 pos);
	private:
		glm::vec3 position;
	};
}
