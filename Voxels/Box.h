#pragma once
#include <glm.hpp>
#include <gl/glew.h>

namespace Voxels {
	class Box {
	public:
		Box();
		Box(glm::vec3 pos, float scale);
		~Box();
		void init();
		void render();
	private:
		float scale;
		GLuint vbo[2];
		glm::vec3 position;
	};
}

