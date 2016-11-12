#pragma once
#include <glm.hpp>
#include <gl/glew.h>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

namespace Voxels {
	class Light {
	public:
		Light(glm::vec3 pos);
		~Light();
		glm::vec3 getPosition();
		GLfloat *getPositionPtr();
		void setPosition(glm::vec3 pos);
		glm::vec3 getDirection();
		void setDirection(glm::vec3 dir);
		glm::mat4 getVP();
		GLfloat *getVPPtr();
	protected:
		void updateView();
	private:
		glm::vec3 position;
		glm::vec3 direction;
		glm::mat4 projection;
		glm::mat4 view;
		glm::mat4 VP;
	};
}
