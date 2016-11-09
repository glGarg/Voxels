#pragma once

namespace Voxels {
	class Block {
	public:
		Block();
		~Block();
		void setActive(bool active);
		bool isActive();
		static float BLOCK_SIZE;
	private:
		bool active;
	};
}