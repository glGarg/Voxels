#include "Window.h"

namespace Voxels {
	static void keyboardInputFunc(GLFWwindow *window, int key, int, int action, int) {
		if (action == GLFW_RELEASE) {
			switch (key) {
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GLFW_TRUE);
				break;
			default:
				break;
			}
		}
	}

	static void resizeFunc(GLFWwindow *window, int width, int height) {}

	static void mouseInputFunc(GLFWwindow *window, int key, int action, int) {}

	Window::Window(int width, int height, string windowName) : width(width), height(height), window(nullptr), keyboardFunc(keyboardInputFunc), mouseFunc(mouseInputFunc), resizeFunc(resizeFunc) {
		if (glfwInit()) {
			window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);
			glfwMakeContextCurrent(window);
			if (!glewInit()) {
				//glew not initialized
			}

			glfwSetKeyCallback(window, keyboardFunc);
			glfwSetMouseButtonCallback(window, mouseFunc);
			glfwSetCursorPosCallback(window, cursorFunc);
			glfwSetWindowSizeCallback(window, resizeFunc);
		}
		else {
			//glfw not initialized
		}
	}

	Window::~Window() {
		glfwDestroyWindow(window);
	}

	void Window::init() {
		glClearColor(1, 1, 1, 1.);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glDepthRange(0., 1.);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Window::setWindowSize(int width, int height) {
		this->width = width;
		this->height = height;
	}

	glm::vec2 Window::getWindowSize() {
		return glm::vec2(width, height);
	}

	bool Window::windowShouldClose() {
		return glfwWindowShouldClose(window);
	}

	Window::operator bool() {
		return glfwWindowShouldClose(window);
	}

	void Window::swapBuffers() {
		glfwSwapBuffers(window);
	}

	double Window::getTime() {
		return glfwGetTime();
	}

	glm::vec2 Window::getMouseCoords() {
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		glfwSetCursorPos(window, x, y);
		return glm::vec2(x, y);
	}

	glm::vec2 Window::getMouseCoordsNormal() {
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		glfwSetCursorPos(window, x, y);
		return glm::vec2(x / width, y / height);
	}

	void Window::pollEvents() {
		glfwPollEvents();
	}

	void Window::setKeyboardFunc(void(*keyboardFunction)(GLFWwindow *, int, int, int, int)) {
		keyboardFunc = keyboardFunction;
		glfwSetKeyCallback(window, keyboardFunc);
	}

	void Window::setMouseFunc(void(*mouseFunction)(GLFWwindow *, int, int, int)) {
		mouseFunc = mouseFunction;
		glfwSetMouseButtonCallback(window, mouseFunc);
	}

	void Window::setCursorFunc(void(*cursorFunction)(GLFWwindow *, double, double)) {
		cursorFunc = cursorFunction;
		glfwSetCursorPosCallback(window, cursorFunc);
	}

	void Window::setWindowPointer(void *pointer) {
		if (nullptr != pointer) {
			glfwSetWindowUserPointer(window, pointer);
		}
	}
}