#include "Block.h"

namespace Voxels {
	float Block::BLOCK_SIZE = 0.5;

	Block::Block(BlockType type) : active(true), type(type) {}

	Block::~Block() {}

	void Block::setActive(bool active) {
		this->active = active;
	}

	bool Block::isActive() {
		return active;
	}
}
