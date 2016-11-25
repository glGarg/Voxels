#include "Renderer.h"

namespace Voxels {
	Renderer::Renderer() : vbo{ 0, 0, 0 }, vao(0) {}

	Renderer::~Renderer() {}

	void Renderer::addTriangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2) {
		vertices.push_back(v0);
		vertices.push_back(v1);
		vertices.push_back(v2);
	}

	void Renderer::addType(BlockType type) {
		types.push_back(type);
		types.push_back(type);
		types.push_back(type);
	}

	void Renderer::addAO(float AO) {
		AOvals.push_back(AO);
	}

	void Renderer::update() {
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, types.size() * sizeof(int), types.data(), GL_STATIC_DRAW);
		glVertexAttribIPointer(1, 1, GL_INT, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, AOvals.size() * sizeof(float), AOvals.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Renderer::clear() {
		vertices.clear();
		types.clear();
		AOvals.clear();
	}

	void Renderer::init() {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(3, vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glEnableVertexAttribArray(1);
		glVertexAttribIPointer(1, 1, GL_INT, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, 0);

		glBindVertexArray(0);
	}

	void Renderer::render() {
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		glBindVertexArray(0);
	}
}
