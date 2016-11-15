#include "Chunk.h"

namespace Voxels {
	const int Chunk::CHUNK_SIZE = 16;

	Chunk::Chunk() : position(0.), renderer(new Renderer) {
		allocBlocks();
	}

	Chunk::Chunk(glm::vec3 pos) : position(pos), renderer(new Renderer) {
		allocBlocks();
	}

	Chunk::~Chunk() {
		for (int i = 0; i < CHUNK_SIZE; ++i) {
			for (int j = 0; j < CHUNK_SIZE; ++j) {
				delete[] blocks[i][j];
			}
			delete[] blocks[i];
		}
		delete[] blocks;
		delete renderer;
	}

	void Chunk::init() {
		renderer->init();
		update();
	}

	void Chunk::render() {
		renderer->render();
	}

	void Chunk::update() {
		renderer->clear();
		for (int i = 0; i > -CHUNK_SIZE; --i) {
			for (int j = 0; j > -CHUNK_SIZE; --j) {
				for (int k = 0; k > -CHUNK_SIZE; --k) {
					if (!blocks[-i][-j][-k].isActive()) {
						continue;
					}
					if (noise.GetSimplex(2.*(position.x + i), 3*(position.y + j), 4*(position.z + k)) < 0.2f) {
						createCube(position + Chunk::CHUNK_SIZE*.5f + glm::vec3(i, j, k));
					}
				}
			}
		}
		renderer->update();
	}

	void Chunk::allocBlocks() {
		blocks = new Block **[CHUNK_SIZE];
		for (int i = 0; i < CHUNK_SIZE; ++i) {
			blocks[i] = new Block *[CHUNK_SIZE];
			for (int j = 0; j < CHUNK_SIZE; ++j) {
				blocks[i][j] = new Block[CHUNK_SIZE];
			}
		}
	}

	void Chunk::setPosition(glm::vec3 pos) {
		position = pos;
	}

	void Chunk::createCube(glm::vec3 pos, BlockType type) {
		glm::vec3 vertexData[36] = {
			glm::vec3(-1.0f, -1.0f, -1.0f),		glm::vec3(-1.0f, -1.0f, 1.0f),		glm::vec3(-1.0f, 1.0f, 1.0f),
			glm::vec3(1.0f, 1.0f, -1.0f),		glm::vec3(-1.0f, -1.0f, -1.0f),		glm::vec3(-1.0f, 1.0f, -1.0f),
			glm::vec3(1.0f, -1.0f, 1.0f),		glm::vec3(-1.0f, -1.0f, -1.0f),		glm::vec3(1.0f, -1.0f, -1.0f),
			glm::vec3(1.0f, 1.0f, -1.0f),		glm::vec3(1.0f, -1.0f, -1.0f),		glm::vec3(-1.0f, -1.0f, -1.0f),
			glm::vec3(-1.0f, -1.0f, -1.0f),		glm::vec3(-1.0f, 1.0f, 1.0f),		glm::vec3(-1.0f, 1.0f, -1.0f),
			glm::vec3(1.0f, -1.0f, 1.0f),		glm::vec3(-1.0f, -1.0f, 1.0f),		glm::vec3(-1.0f, -1.0f, -1.0f),
			glm::vec3(-1.0f, 1.0f, 1.0f),		glm::vec3(-1.0f, -1.0f, 1.0f),		glm::vec3(1.0f, -1.0f, 1.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),		glm::vec3(1.0f, -1.0f, -1.0f),		glm::vec3(1.0f, 1.0f, -1.0f),
			glm::vec3(1.0f, -1.0f, -1.0f),		glm::vec3(1.0f, 1.0f, 1.0f),		glm::vec3(1.0f, -1.0f, 1.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),		glm::vec3(1.0f, 1.0f, -1.0f),		glm::vec3(-1.0f, 1.0f, -1.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),		glm::vec3(-1.0f, 1.0f, -1.0f),		glm::vec3(-1.0f, 1.0f, 1.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),		glm::vec3(-1.0f, 1.0f, 1.0f),		glm::vec3(1.0f, -1.0f, 1.0f)
		};
		for (int i = 0; i < sizeof(vertexData) / sizeof(glm::vec3); i+=3) {
			BlockType cubeType = type;
			if (type == BlockType::GRASS_BLOCK && false /*top face*/) {
				cubeType = BlockType::GRASS_BLOCK;
			}
			renderer->addTriangle(Block::BLOCK_SIZE*(vertexData[i]) + pos,
								  Block::BLOCK_SIZE*(vertexData[i + 1]) + pos,
								  Block::BLOCK_SIZE*(vertexData[i + 2]) + pos);
			renderer->addType(cubeType);
		}
	}
}
