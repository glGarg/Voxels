#pragma once
#include <iostream>
#include <gl/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/constants.hpp>

#define PI 3.141592

namespace Voxels {
	class Camera {
	public:
		Camera();
		Camera(glm::vec3 pos, glm::vec3 dir, float fov, float near, float far, float width, float height); //takes target
		Camera(glm::vec3 pos, float pitch, float yaw, float fov, float near, float far, float width, float height); //takes pitch and yaw
		~Camera();
		void init();
		void setPosition(glm::vec3 pos);
		void setDirection(glm::vec3 pos);
		void setCameraUpdated();
		void setYaw(float yaw);
		void setPitch(float pitch); 

		glm::vec3 getPosition();
		glm::vec3 getDirection();
		bool getCameraUpdated();
		float getYaw();
		float getPitch();
		glm::mat4 getMVP();
		const GLfloat *getMVPPtr();
		glm::vec3 getUp();
		glm::vec3 getRight();
	protected:
		void update();
		void updateView();
		void updateProjection();
	private:
		bool cameraUpdated;
		float fov, near, far, width, height;
		float pitch, yaw;
		glm::vec3 position;
		glm::vec3 direction;
		glm::mat4 model;
		glm::mat4 projection;
		glm::mat4 view;
		glm::mat4 mvp;
	};
}

