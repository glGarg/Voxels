#pragma once
#include "Block.h"
#include <glm.hpp>
#include "Renderer.h"
#include "FastNoise.h"

namespace Voxels {
	class Chunk {
	public:
		Chunk();
		Chunk(glm::vec3 pos);
		~Chunk();
		void render();
		void update();
		void init();
		void setPosition(glm::vec3 pos);
		static const int CHUNK_SIZE;
	private:
		void allocBlocks();
		void createCube(glm::vec3 position, BlockType type = BlockType::DEFAULT_BLOCK);
		glm::vec3 position;
		Renderer *renderer;
		Block ***blocks;
		FastNoise noise;
	};
}
