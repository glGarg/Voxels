#include "Game.h"

#define PI 3.141592

Game::Game(int width, int height) : width(width), height(height),
									window(width, height, "Test"),
									programVertex("./assets/Vertex.glsl", GL_VERTEX_SHADER),
									programFragment("./assets/AOFragment.glsl", GL_FRAGMENT_SHADER),
									depthProgramVertex("./assets/depthVertex.glsl", GL_VERTEX_SHADER),
									depthProgramFragment("./assets/depthFragment.glsl", GL_FRAGMENT_SHADER),
									camera(glm::vec3(120, 120, 120),
									glm::normalize(glm::vec3(0, 0, 0) - glm::vec3(120, 120, 120)),
									glm::radians(25.f), .1, 1000, width, height), framerateController(30), map(3),
									depthTexture(Voxels::TextureLoader::getTextureCount(), width, height, 1, 1),
									depthFrameBuffer()
{
	depthProgram.attach(depthProgramVertex);
	depthProgram.attach(depthProgramFragment);
	depthProgram.link();
	depthProgram.use();

	program.attach(programVertex);
	program.attach(programFragment);
	program.link();
	program.use();

	window.init();
	window.setKeyboardFunc(keyboardInputFunc);
	window.setMouseFunc(mouseInputFunc);
	window.setCursorFunc(cursorInputFunc);
	window.setWindowPointer(&inputHandler);
}

Game::~Game() {}

void Game::run() {
	Voxels::Light light(camera.getPosition());
	map.init();
	camera.init();

	glUniform1i(program.getUniformLocation("texture"), Voxels::ResourceManager::getTexture("./assets/Textures/NM.png")->texture);
	glUniform1i(program.getUniformLocation("atlas"), Voxels::ResourceManager::getTextureAtlas("./assets/Textures/Atlas.png", 4, 4)->texture);
	glUniform1i(program.getUniformLocation("depth"), depthTexture.texture);
	glUniformMatrix4fv(program.getUniformLocation("MVP"), 1, GL_FALSE, camera.getMVPPtr());
	glUniformMatrix4fv(program.getUniformLocation("InverseProjection"), 1, GL_FALSE, camera.getInverseProjectionPtr());
	glUniform3fv(program.getUniformLocation("cameraPos"), 1, camera.getPositionPtr());
	glUniform3fv(program.getUniformLocation("lightPos"), 1, light.getPositionPtr());

	depthFrameBuffer.init();

	depthTexture.init();
	depthTexture.bind();
	depthTexture.setSource(0, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	depthFrameBuffer.bind();
	depthFrameBuffer.attachTexture(GL_DEPTH_ATTACHMENT, depthTexture.id, 0);
	depthFrameBuffer.drawBuffer(GL_NONE);
	if (GL_FRAMEBUFFER_COMPLETE != glCheckFramebufferStatus(GL_FRAMEBUFFER)) {
		cout << "Error incomplete framebuffer" << endl;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	depthFrameBuffer.unbind();

	while (!window) {
		framerateController.begin();

		depthProgram.use();
		glUniformMatrix4fv(depthProgram.getUniformLocation("lightVP"), 1, GL_FALSE, light.getVPPtr());
		glViewport(0, 0, width, height);
		depthFrameBuffer.bind();
		glClear(GL_DEPTH_BUFFER_BIT);
		map.render();
		depthFrameBuffer.unbind();
		depthProgram.disable();

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		program.use();
		processInput();
		if (camera.getCameraUpdated()) {
			light.setPosition(camera.getPosition());
			light.setDirection(camera.getDirection());
			glUniformMatrix4fv(program.getUniformLocation("lightVP"), 1, GL_FALSE, light.getVPPtr());
			glUniform3fv(program.getUniformLocation("cameraPos"), 1, camera.getPositionPtr());
			glUniform3fv(program.getUniformLocation("lightPos"), 1, light.getPositionPtr());
			glUniformMatrix4fv(program.getUniformLocation("MVP"), 1, GL_FALSE, camera.getMVPPtr());
			camera.setCameraUpdated();
		}
		depthTexture.bind();
		map.render();
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
		camera.setYaw(camera.getYaw() - offset.x*.006f);
		camera.setPitch(camera.getPitch() - offset.y*.002f);
	}
	if (inputHandler.isPressed(GLFW_KEY_D)) {
		camera.setPosition(camera.getPosition() + camera.getRight() *.2f);
	}
	if (inputHandler.isPressed(GLFW_KEY_A)) {
		camera.setPosition(camera.getPosition() - camera.getRight() *.2f);
	}
	if (inputHandler.isPressed(GLFW_KEY_W)) {
		camera.setPosition(camera.getPosition() + camera.getUp() *.2f);
	}
	if (inputHandler.isPressed(GLFW_KEY_S)) {
		camera.setPosition(camera.getPosition() - camera.getUp() *.2f);
	}
	if (inputHandler.isPressed(GLFW_KEY_UP)) {
		camera.setPosition(camera.getPosition() + camera.getDirection() * .2f);
	}
	if (inputHandler.isPressed(GLFW_KEY_DOWN)) {
		camera.setPosition(camera.getPosition() - camera.getDirection() * .2f);
	}
}
