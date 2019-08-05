#pragma once

#include "HUD.h"
#include "Player.h"
#include "World.h"

class Renderer {
private:
	GLFWwindow* window;
	TextureAtlas entityAtlas;

	// Frame Counter
	const std::string WINDOW_TITLE = "Voxel Engine";
	double prevFrameTime;
	unsigned int frameCount = 0;
	void updateWindowTitle();
public:
	Renderer();
	GLFWwindow* initWindow();

	HUD hud;
	World world;
	Player player;

	bool isRunning() { return !glfwWindowShouldClose(window); };
	void render();
	void handleEvents();
};

void APIENTRY glDebugCallback(GLenum source, GLenum mType, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam);

