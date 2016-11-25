#include "Block.h"

namespace Voxels {
	float Block::BLOCK_SIZE = 0.5;

	Block::Block(BlockType type) : active(false), type(type) {}

	Block::~Block() {}

	void Block::setActive(bool active) {
		this->active = active;
	}

	bool Block::isActive() {
		return active;
	}

	void Block::setType(BlockType type) {
		this->type = type;
	}

	BlockType Block::getType() {
		return type;
	}
}
