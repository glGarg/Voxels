#include "Game.h"

#define PI 3.141592

Game::Game(int width, int height) : width(width), height(height),
									window(width, height, "Test"),
									vertex("./assets/Vertex.glsl", GL_VERTEX_SHADER),
									fragment("./assets/Fragment.glsl", GL_FRAGMENT_SHADER),
									camera(glm::vec3(20, 20, 20), glm::normalize(glm::vec3(0, 0, 0) - glm::vec3(20, 20, 20)), glm::radians(25.f), 0.1, 1000, width, height),
									framerateController(30)
{
	program.attach(vertex);
	program.attach(fragment);
	program.link();
	program.use();

	window.init();
	window.setKeyboardFunc(keyboardInputFunc);
	window.setMouseFunc(mouseInputFunc);
	window.setCursorFunc(cursorInputFunc);
	window.setWindowPointer(&inputHandler);
}

Game::~Game() {}

void Game::run()
{
	/*vector<Voxels::Box> boxes;
	vector<glm::vec3> positions;
	for (float i = 0; i > -10; i-=2.3) {
		for (float j = 0; j > -10; j-=2.3) {
			for (float k = 0; k > -10; k-=2.3) {
				positions.emplace_back(i, j, k);
			}
		}
	}
	for (int i = 0; i < positions.size(); ++i) {
		boxes.emplace_back(positions[i]);
		boxes[i].init();
	}*/
	Voxels::Light light(glm::vec3(0., 15., 0));
	
	//Voxels::Box box(glm::vec3(0, 15, 0), 0.3);
	Voxels::Chunk chunk(glm::vec3(0., 0., 0.));
	
	//box.init();
	chunk.init();
	
	camera.init();

	glUniform1i(program.getUniformLocation("texture"), Voxels::ResourceManager::getTexture("./assets/Textures/Wood.jpg")->texture);
	glUniformMatrix4fv(program.getUniformLocation("MVP"), 1, GL_FALSE, camera.getMVPPtr());
	glUniform3fv(program.getUniformLocation("lightPos"), 1, light.getPositionPtr());

	while (!window) {
		framerateController.begin();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		program.use();
		processInput();
		if (camera.getCameraUpdated()) {
			light.setPosition(camera.getPosition());
			glUniformMatrix4fv(program.getUniformLocation("MVP"), 1, GL_FALSE, camera.getMVPPtr());
			camera.setCameraUpdated();
		}

		/*for (int i = boxes.size(); i > 0; --i) {
			boxes[i-1].draw();
		}*/

		chunk.render();
		//box.render();

		program.disable();
		
		window.pollEvents();
		framerateController.end();
		window.swapBuffers();
	}
}
void Game::keyboardInputFunc(GLFWwindow *window, int key, int, int action, int) {
	Voxels::InputHandler *handler = (Voxels::InputHandler *)glfwGetWindowUserPointer(window);
	handler->handleButtonInput(key, action);
}

void Game::mouseInputFunc(GLFWwindow *window, int key, int action, int) {
	Voxels::InputHandler *handler = (Voxels::InputHandler *)glfwGetWindowUserPointer(window);
	handler->handleButtonInput(key, action);
}

void Game::cursorInputFunc(GLFWwindow *window, double x, double y) {
	Voxels::InputHandler *handler = (Voxels::InputHandler *)glfwGetWindowUserPointer(window);
	handler->handleCursorInput(x, y);
}

void Game::processInput() {
	if (inputHandler.cursorMoved()) {
		glm::vec2 offset(inputHandler.getXOffset(), inputHandler.getYOffset());
		//camera.setYaw(camera.getYaw() - offset.x*.001f);
		//camera.setPitch(camera.getPitch() - offset.y*.001f);
	}
	if (inputHandler.isPressed(GLFW_KEY_RIGHT)) {
		camera.setPosition(camera.getPosition() + camera.getRight() *.2f);
	}
	if (inputHandler.isPressed(GLFW_KEY_LEFT)) {
		camera.setPosition(camera.getPosition() - camera.getRight() *.2f);
	}
	if (inputHandler.isPressed(GLFW_KEY_UP)) {
		camera.setPosition(camera.getPosition() + camera.getDirection() * .2f);
	}
	if (inputHandler.isPressed(GLFW_KEY_DOWN)) {
		camera.setPosition(camera.getPosition() - camera.getDirection() * .2f);
	}
}
