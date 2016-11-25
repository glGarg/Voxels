#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

using std::string;

namespace Voxels {
	enum WindowState {
		//Add window states for window
	};

	class Window {
	public:
		Window(int width, int height, string windowName);
		~Window();
		void init();
		void setWindowSize(int width, int height);
		void swapBuffers();
		void pollEvents();
		bool windowShouldClose();
		operator bool();
		glm::vec2 getWindowSize();
		double getTime();
		glm::vec2 getMouseCoords();
		glm::vec2 getMouseCoordsNormal();
		void setKeyboardFunc(void(*keyboardFunc)(GLFWwindow *, int, int, int, int));
		void setMouseFunc(void(*mouseFunc)(GLFWwindow *, int, int, int));
		void setCursorFunc(void(*cursorFunction)(GLFWwindow *, double, double));
		void setWindowPointer(void *pointer);
	public:
		int width, height;
		GLFWwindow *window;
		void(*keyboardFunc)(GLFWwindow *, int, int, int, int);
		void(*mouseFunc)(GLFWwindow *, int, int, int);
		void(*cursorFunc)(GLFWwindow *, double, double);
		void(*resizeFunc)(GLFWwindow *, int, int);
	};
}