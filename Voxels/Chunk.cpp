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
					glm::vec3 df(2.*(((float)-i) / CHUNK_SIZE) - .5,
								 2.*(((float)-j) / CHUNK_SIZE) - .5,
								 2.*(((float)-k) / CHUNK_SIZE) - .5);
					if (terrain(2.*(position.x + i), 3 * (position.y + j), 4 * (position.z + k), df.x, df.y, df.z) > 0.f) {
						glm::vec3 DF(2.*(((float)-i+1) / CHUNK_SIZE) - .5,
									 2.*(((float)-j+1) / CHUNK_SIZE) - .5,
									 2.*(((float)-k+1) / CHUNK_SIZE) - .5);
						if (j - 1 >= -1 || terrain(2.*(position.x + i), 3 * (position.y + j + 1), 4 * (position.z + k), DF.x, DF.y, DF.z) <= 0.f) {
							createCube(position + CHUNK_SIZE*.5f + glm::vec3(i, j, k), BlockType::GRASS_BLOCK);
						}
						else {
							createCube(position + CHUNK_SIZE*.5f + glm::vec3(i, j, k));
						}
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
			BlockType cubeType = BlockType::DEFAULT_BLOCK;
			if (type == BlockType::GRASS_BLOCK && (i == 27 || i == 30)) {
				cubeType = BlockType::GRASS_BLOCK; //top face	
			}
			renderer->addTriangle(Block::BLOCK_SIZE*(vertexData[i]) + pos,
								  Block::BLOCK_SIZE*(vertexData[i + 1]) + pos,
								  Block::BLOCK_SIZE*(vertexData[i + 2]) + pos);
			renderer->addType(cubeType);
		}
	}
	//adjust the values from 0 to -1 rather than 1 to 0
	float Chunk::terrain(float x, float y, float z, float dx, float dy, float dz) {
		dx += 1.;
		dy += 1.;
		dz += 1.;

		float density = 0, plateau, center;
		if (dy > 0.9) {
			return 0.;	//cut off height
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
