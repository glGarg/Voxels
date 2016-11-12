#pragma once
#include <vector>
#include "Chunk.h"

using std::vector;

namespace Voxels {
	class Map {
	public:
		Map(unsigned int size = 4);
		~Map();
		void init();
		void render();
	private:
		unsigned const int size;
		vector<Chunk *> chunks;
	};
}