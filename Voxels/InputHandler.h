#pragma once
#include <map>
#include <glfw/glfw3.h>

using std::map;

namespace Voxels {
	class InputHandler {
	public:
		InputHandler();
		~InputHandler();
		void handleButtonInput(int key, int action);
		void handleCursorInput(float x, float y);
		float getXOffset();
		float getYOffset();
		bool cursorMoved();
		bool isPressed(int key);
	private:
		float x, y, lastx, lasty, dx, dy;
		bool cursorMove;
		map<int, bool> buttonMap;
	};
}
