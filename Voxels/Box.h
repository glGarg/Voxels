#pragma once
#include <glm.hpp>
#include <gl/glew.h>

namespace Voxels {
	class Box {
	public:
		Box();
		Box(glm::vec3 pos);
		~Box();
		void init();
		void draw();
	private:
		GLuint vbo[2];
		glm::vec3 position;
	};
}

