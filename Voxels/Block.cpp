#include "Block.h"

namespace Voxels {
	float Block::BLOCK_SIZE = 0.3;

	Block::Block() : active(true) {}

	Block::~Block() {}

	void Block::setActive(bool active) {
		this->active = active;
	}

	bool Block::isActive() {
		return active;
	}
}