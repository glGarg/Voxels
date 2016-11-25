#pragma once
#include "Block.h"
#include <glm.hpp>
#include "Renderer.h"
#include "FastNoise.h"
#include <iostream>

namespace Voxels {
	class Chunk {
	public:
		Chunk(bool top);
		Chunk(bool top, glm::vec3 pos);
		~Chunk();
		void render();
		void update();
		void init();
		void setPosition(glm::vec3 pos);
		static const int CHUNK_SIZE;
	private:
		void allocBlocks();
		void createCube(glm::vec3 position, glm::vec3 indices, BlockType type = BlockType::DEFAULT_BLOCK);
		float calcAO(glm::vec3 vertex, glm::vec3 indices);
		float terrain(float x, float y, float z, float dx, float dy, float dz);
		const bool top;
		glm::vec3 position;
		Renderer *renderer;
		Block ***blocks;
		FastNoise noise;
	};
}
