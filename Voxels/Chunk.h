#pragma once
#include "Block.h"
#include <glm.hpp>
#include "Renderer.h"

namespace Voxels {
	class Chunk {
	public:
		Chunk();
		Chunk(glm::vec3 pos);
		~Chunk();
		void render();
		void update();
		void init();
		static const int CHUNK_SIZE;
	private:
		void allocBlocks();
		void createCube(glm::vec3 position);
		glm::vec3 position;
		Renderer *renderer;
		Block ***blocks;
	};
}
