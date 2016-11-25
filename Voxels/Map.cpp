#include "Map.h"


namespace Voxels {
	Map::Map(unsigned int size) : size(size), chunks(size * size * size) {}

	Map::~Map() {
		for (vector<Chunk *>::iterator it = chunks.begin(); it != chunks.end(); it++) {
			if (nullptr != *it) {
				delete *it;
			}
		}
	}

	void Map::init() {
		for (float i = 0; i < size; ++i) {
			for (float j = 0; j < size; ++j) {
				for (float k = 0; k < size; ++k) {
					bool top = j == (size - 1);
					chunks[size * size * i + size * j + k] = new Chunk(top, glm::vec3(i * Voxels::Chunk::CHUNK_SIZE,
																			j * Voxels::Chunk::CHUNK_SIZE,
																			k * Voxels::Chunk::CHUNK_SIZE));
					chunks[size * size * i + size * j + k]->init();
				}
			}
		}
	}

	void Map::render() {
		for (float i = 0; i < size; ++i) {
			for (float j = 0; j < size; ++j) {
				for (float k = 0; k < size; ++k) {
					chunks[size * size * i + size * j + k]->render();
				}
			}
		}
	}
}