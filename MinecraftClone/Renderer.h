#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Cube.h"
#include "Object.h"
#include "Shader.h"

class Renderer {
private:
	GLFWwindow* window;
	Camera camera;

	// Shaders
	Shader cubeShader;

	std::list<std::unique_ptr<Object>> objects;
public:
	Renderer();
	GLFWwindow* initWindow();

	bool isRunning() { return !glfwWindowShouldClose(window); };
	void addCube(float x, float y, float z) { objects.push_back(std::make_unique<Cube>(cubeShader, x, y, z)); }
	void render();
	void handleEvents();
};

void APIENTRY glDebugCallback(GLenum source, GLenum mType, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam);

