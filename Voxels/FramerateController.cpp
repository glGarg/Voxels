#include "FramerateController.h"

namespace Voxels {
	FramerateController::FramerateController(float framerate) : framerate(framerate) {}

	FramerateController::FramerateController() : framerate(30) {}

	FramerateController::~FramerateController() {}

	void FramerateController::setFramerate(float framerate) {
		if (framerate > 0) {
			this->framerate = framerate;
		}
	}

	void FramerateController::displayFramerate() {
		static float lastTimestamp = glfwGetTime();
		static int frames = 0;
		frames++;
		if (glfwGetTime() - lastTimestamp >= 1.f) {
			cout << "FPS = " << frames << endl;
			frames = 0;
			lastTimestamp = glfwGetTime();
		}
	}

	void FramerateController::begin() {
		startTime = glfwGetTime();
	}

	void FramerateController::end() {
		endTime = glfwGetTime();
		if ((startTime - endTime) < 1.f / framerate) {
			glfwWaitEventsTimeout(1.f / framerate - (startTime - endTime));
		}
	}
}
