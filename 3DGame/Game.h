#pragma once
#include <Voxels/Window.h>
#include <Voxels/Program.h>
#include <Voxels/Shader.h>
#include <Voxels/Window.h>
#include <Voxels/Box.h>
#include <Voxels/Camera.h>
#include <Voxels/InputHandler.h>
#include <Voxels/FramerateController.h>
#include <Voxels/Chunk.h>
#include <Voxels/Light.h>
#include <Voxels/ResourceManager.h>
#include <Voxels/Texture.h>

class Game {
public:
	Game(int width, int height);
	~Game();
	void run();
	static void keyboardInputFunc(GLFWwindow *window, int key, int, int action, int);
	static void mouseInputFunc(GLFWwindow *window, int key, int action, int);
	static void cursorInputFunc(GLFWwindow *window, double x, double y);
protected:
	void processInput();
private:
	int width, height;
	Voxels::Window window;
	Voxels::Program program;
	Voxels::Shader vertex;
	Voxels::Shader fragment;
	Voxels::Camera camera;
	Voxels::InputHandler inputHandler;
	Voxels::FramerateController framerateController;
};
