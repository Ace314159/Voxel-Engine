#pragma once

#include "Camera.h"
#include "HUD.h"
#include "World.h"

class Renderer {
private:
	GLFWwindow* window;
	Camera camera;

	// Frame Counter
	const std::string WINDOW_TITLE = "Minecraft Clone";
	double prevFrameTime;
	unsigned int frameCount = 0;
	void updateWindowTitle();
public:
	Renderer();
	GLFWwindow* initWindow();

	HUD hud;
	World world;

	bool isRunning() { return !glfwWindowShouldClose(window); };
	void render();
	void handleEvents();
};

void APIENTRY glDebugCallback(GLenum source, GLenum mType, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam);

