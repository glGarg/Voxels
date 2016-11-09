#include "Chunk.h"

namespace Voxels {
	const int Chunk::CHUNK_SIZE = 10;

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
		for (int i = 0; i < CHUNK_SIZE; ++i) {
			for (int j = 0; j < CHUNK_SIZE; ++j) {
				for (int k = 0; k < CHUNK_SIZE; ++k) {
					if (!blocks[i][j][k].isActive()) {
						continue;
					}
					createCube(position + glm::vec3(-i, -j, -k));
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

	void Chunk::createCube(glm::vec3 pos) {
		/*glm::vec3 p1(pos.x - Block::BLOCK_SIZE, pos.y - Block::BLOCK_SIZE, pos.z + Block::BLOCK_SIZE);
		glm::vec3 p2(pos.x + Block::BLOCK_SIZE, pos.y - Block::BLOCK_SIZE, pos.z + Block::BLOCK_SIZE);
		glm::vec3 p3(pos.x + Block::BLOCK_SIZE, pos.y + Block::BLOCK_SIZE, pos.z + Block::BLOCK_SIZE);
		glm::vec3 p4(pos.x - Block::BLOCK_SIZE, pos.y + Block::BLOCK_SIZE, pos.z + Block::BLOCK_SIZE);
		glm::vec3 p5(pos.x + Block::BLOCK_SIZE, pos.y - Block::BLOCK_SIZE, pos.z - Block::BLOCK_SIZE);
		glm::vec3 p6(pos.x - Block::BLOCK_SIZE, pos.y - Block::BLOCK_SIZE, pos.z - Block::BLOCK_SIZE);
		glm::vec3 p7(pos.x - Block::BLOCK_SIZE, pos.y + Block::BLOCK_SIZE, pos.z - Block::BLOCK_SIZE);
		glm::vec3 p8(pos.x + Block::BLOCK_SIZE, pos.y + Block::BLOCK_SIZE, pos.z - Block::BLOCK_SIZE);
		renderer->addTriangle(p1, p2, p3);
		renderer->addTriangle(p1, p3, p4);

		renderer->addTriangle(p5, p6, p7);
		renderer->addTriangle(p5, p7, p8);

		renderer->addTriangle(p2, p5, p8);
		renderer->addTriangle(p2, p8, p3);

		renderer->addTriangle(p6, p1, p4);
		renderer->addTriangle(p6, p4, p7);
		
		renderer->addTriangle(p4, p3, p8);
		renderer->addTriangle(p4, p8, p7);

		renderer->addTriangle(p6, p5, p2);
		renderer->addTriangle(p6, p2, p1);
		*/
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
			vertexData[i] = Block::BLOCK_SIZE*vertexData[i] + pos;
			vertexData[i+1] = Block::BLOCK_SIZE*vertexData[i+1] + pos;
			vertexData[i+2] = Block::BLOCK_SIZE*vertexData[i+2] + pos;
			renderer->addTriangle(vertexData[i], vertexData[i + 1], vertexData[i + 2]);
		}
	}
}
