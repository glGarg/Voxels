#include "InputHandler.h"

namespace Voxels {
	InputHandler::InputHandler() : x(0), y(0), lastx(250), lasty(250), dx(0), dy(0)
	{}

	InputHandler::~InputHandler() {}

	void InputHandler::handleButtonInput(int key, int action) {
		if (action == GLFW_RELEASE) {
			buttonMap[key] = false;
		}
		else if (action == GLFW_PRESS) {
			buttonMap[key] = true;
		}
	}

	void InputHandler::handleCursorInput(float x, float y) {
		dx = x - lastx;
		dy = lasty - y;
		lastx = x;
		lasty = y;
		cursorMove = true;
	}

	bool InputHandler::cursorMoved() {
		if (true == cursorMove) {
			cursorMove = false;
			return true;
		}
		return false;
	}

	float InputHandler::getXOffset() {
		return dx;
	}

	float InputHandler::getYOffset() {
		return dy;
	}

	bool InputHandler::isPressed(int key) {
		return (buttonMap.find(key) != buttonMap.end()) ? buttonMap[key] : false;
	}
}
