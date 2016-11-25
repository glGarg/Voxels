#include "Chunk.h"

namespace Voxels {
	const int Chunk::CHUNK_SIZE = 16;

	Chunk::Chunk(bool top) : top(top), position(0.), renderer(new Renderer) {
		allocBlocks();
	}

	Chunk::Chunk(bool top, glm::vec3 pos) : top(top), position(pos), renderer(new Renderer) {
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
					if (blocks[-i][-j][-k].isActive()) {
						createCube(position + CHUNK_SIZE*.5f + glm::vec3(i, j, k), glm::vec3(-i, -j, -k), blocks[-i][-j][-k].getType());
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
				for (int k = 0; k < CHUNK_SIZE; k++) {
					if (noise.GetSimplex(2.*(position.x - i), 3 * (position.y - j), 4 * (position.z - k)) < 0.1f) {
						blocks[i][j][k].setActive(true);
						if (-j - 1 >= -1 || noise.GetSimplex(2.*(position.x - i), 3 * (position.y - j + 1), 4 * (position.z - k)) >= 0.1f) {
							if (top && -j - 1 >= -2) { //topmost layer
								blocks[i][j][k].setType(BlockType::SNOW_BLOCK);
							}
							else if (-j - 1 < -2) {
								blocks[i][j][k].setType(BlockType::GRASS_BLOCK);
							}
						}
					}
				}
			}
		}
	}

	void Chunk::setPosition(glm::vec3 pos) {
		position = pos;
	}

	void Chunk::createCube(glm::vec3 pos, glm::vec3 indices, BlockType type) {
		glm::vec3 vertexData[36] = {
			glm::vec3(-1.0f, -1.0f, -1.0f),		glm::vec3(-1.0f, -1.0f, 1.0f),		glm::vec3(-1.0f, 1.0f, 1.0f), //left
			glm::vec3(1.0f, 1.0f, -1.0f),		glm::vec3(-1.0f, -1.0f, -1.0f),		glm::vec3(-1.0f, 1.0f, -1.0f), //near
			glm::vec3(1.0f, -1.0f, 1.0f),		glm::vec3(-1.0f, -1.0f, -1.0f),		glm::vec3(1.0f, -1.0f, -1.0f), //bottom
			glm::vec3(1.0f, 1.0f, -1.0f),		glm::vec3(1.0f, -1.0f, -1.0f),		glm::vec3(-1.0f, -1.0f, -1.0f), //near
			glm::vec3(-1.0f, -1.0f, -1.0f),		glm::vec3(-1.0f, 1.0f, 1.0f),		glm::vec3(-1.0f, 1.0f, -1.0f), //left
			glm::vec3(1.0f, -1.0f, 1.0f),		glm::vec3(-1.0f, -1.0f, 1.0f),		glm::vec3(-1.0f, -1.0f, -1.0f), //bottom
			glm::vec3(-1.0f, 1.0f, 1.0f),		glm::vec3(-1.0f, -1.0f, 1.0f),		glm::vec3(1.0f, -1.0f, 1.0f), //far
			glm::vec3(1.0f, 1.0f, 1.0f),		glm::vec3(1.0f, -1.0f, -1.0f),		glm::vec3(1.0f, 1.0f, -1.0f), //right
			glm::vec3(1.0f, -1.0f, -1.0f),		glm::vec3(1.0f, 1.0f, 1.0f),		glm::vec3(1.0f, -1.0f, 1.0f), //right
			glm::vec3(1.0f, 1.0f, 1.0f),		glm::vec3(1.0f, 1.0f, -1.0f),		glm::vec3(-1.0f, 1.0f, -1.0f), //top
			glm::vec3(1.0f, 1.0f, 1.0f),		glm::vec3(-1.0f, 1.0f, -1.0f),		glm::vec3(-1.0f, 1.0f, 1.0f), //top
			glm::vec3(1.0f, 1.0f, 1.0f),		glm::vec3(-1.0f, 1.0f, 1.0f),		glm::vec3(1.0f, -1.0f, 1.0f) //far
		};
		for (int i = 0; i < sizeof(vertexData) / sizeof(glm::vec3); i+=3) {
			BlockType cubeType = BlockType::DEFAULT_BLOCK;
			if (type != BlockType::DEFAULT_BLOCK) {
					cubeType = type;
			}
			renderer->addTriangle(Block::BLOCK_SIZE*(vertexData[i]) + pos,
								  Block::BLOCK_SIZE*(vertexData[i + 1]) + pos,
								  Block::BLOCK_SIZE*(vertexData[i + 2]) + pos);
			renderer->addType(cubeType);
			renderer->addAO(calcAO(vertexData[i] + 1.f, indices));
			renderer->addAO(calcAO(vertexData[i + 1] + 1.f, indices));
			renderer->addAO(calcAO(vertexData[i + 2] + 1.f, indices));
		}
	}

	float Chunk::calcAO(glm::vec3 vertex, glm::vec3 indices) {
		if ((((vertex.x == 2) && indices.x == 0) ||
			 ((vertex.y == 2) && indices.y == 0) ||
			 ((vertex.z == 2) && indices.z == 0)) ||
		(((vertex.x == 0) && indices.x == CHUNK_SIZE - 1) ||
		 ((vertex.y == 0) && indices.y == CHUNK_SIZE - 1) ||
		 ((vertex.z == 0) && indices.z == CHUNK_SIZE - 1))) {
			return 1.;
		}
		float AO = 1.;
		int y = vertex.y == 0 ? indices.y + 1 : indices.y - 1;
		int x1 = indices.x;
		int z1 = vertex.z == 0 ? indices.z + 1 : indices.z - 1;
		int x2 = vertex.x == 0 ? indices.x + 1 : indices.x - 1;
		int z2 = indices.z;
		int x3 = vertex.x == 0 ? indices.x + 1 : indices.x - 1;
		int z3 = vertex.z == 0 ? indices.z + 1 : indices.z - 1;
		if (blocks[x1][y][z1].isActive() && blocks[x2][y][z2].isActive()) {
			AO = 0.75;
		}
		else if ((blocks[x1][y][z1].isActive() && blocks[x3][y][z3].isActive()) ||
				 (blocks[x2][y][z2].isActive() && blocks[x3][y][z3].isActive())) {
			AO = 0.85;
		}
		else if (blocks[x1][y][z1].isActive() ||
				 blocks[x2][y][z2].isActive() ||
				 blocks[x3][y][z3].isActive()) {
			AO = 0.93;
		}
		else {
			AO = 1.;
		}
		return AO;
	}

	//implement a more interesting noise
	//adjust the values from 0 to -1 instead of 1 to 0
	float Chunk::terrain(float x, float y, float z, float dx, float dy, float dz) {
		dx += 1.;
		dy += 1.;
		dz += 1.;

		float density = 0, plateau, center;
		if (dy > 0.9) {
			return 0.; //zero after cut off height
		}
		else if (dy > 0.8) {
			plateau = 1. - (dy - .8)*10.; //gradually decrease to the top
		}
		else {
			plateau = 1.;
		}
		center = .1 / (pow((dx - 0.5)*1.5, 2.) +
					   pow((dy - 1.)*.8, 2.) +
					   pow((dz -.5)*1.5, 2.));
		density = (noise.GetSimplexFractal(x, y, z)*center*plateau);
		density *= pow(noise.GetSimplexFractal((dx + 1)*3., (dy + 1)*3., (dz + 1.)*3.)+.4, 1.8);
		return density;
	}
}
