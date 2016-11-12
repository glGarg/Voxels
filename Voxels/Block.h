#pragma once

namespace Voxels {
	enum class BlockType {
		DEFAULT_BLOCK = 0,
		GRASS_BLOCK,
		DIRT_BLOCK,
		WATER_BLOCK
	};

	class Block {
	public:
		Block(BlockType type = BlockType::DEFAULT_BLOCK);
		~Block();
		void setActive(bool active);
		bool isActive();
		static float BLOCK_SIZE;
	private:
		bool active;
		BlockType type;
	};
}
