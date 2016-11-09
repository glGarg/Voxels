#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm.hpp>

using std::vector;

namespace Voxels {
	class Renderer
	{
	public:
		Renderer();
		~Renderer();
		void addTriangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2);
		void init();
		void clear();
		void update();
		void render();
	private:
		vector<glm::vec3> vertices;
		GLuint vao;
		GLuint vbo[2];
	};
}