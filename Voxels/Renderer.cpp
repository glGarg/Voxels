#include "Renderer.h"

namespace Voxels {
	Renderer::Renderer() : vbo{ 0, 0 }, vao(0) {}

	Renderer::~Renderer() {}

	void Renderer::addTriangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2) {
		vertices.push_back(v0);
		vertices.push_back(v1);
		vertices.push_back(v2);
	}

	void Renderer::update() {
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Renderer::clear() {
		vertices.clear();
	}

	void Renderer::init() {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindVertexArray(0);
	}

	void Renderer::render() {
		glBindVertexArray(vao);
		for (int i = 36000 - 36; i >= 0; i -= 36) {
			glDrawArrays(GL_TRIANGLES, i, 36);
		}
		//glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		glBindVertexArray(0);
	}
}