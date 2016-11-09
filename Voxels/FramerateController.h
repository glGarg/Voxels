#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

using std::cout;
using std::endl;

namespace Voxels {
	class FramerateController {
	public:
		FramerateController();
		FramerateController(float framerate);
		~FramerateController();
		void setFramerate(float framerate);
		void displayFramerate();
		void begin();
		void end();
	private:
		float framerate;
		float startTime;
		float endTime;
	};
}