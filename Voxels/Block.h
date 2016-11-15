#pragma once

namespace Voxels {
	enum class BlockType {
		DEFAULT_BLOCK = 0,
		DIRT_BLOCK = 3,
		WATER_BLOCK = 9,
		GRASS_BLOCK = 14
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
