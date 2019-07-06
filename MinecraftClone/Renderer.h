#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Block.h"
#include "Camera.h"
#include "HUD.h"
#include "Object.h"
#include "Shader.h"
#include "Texturesheet.h"

class Renderer {
private:
	GLFWwindow* window;
	Camera camera;

	HUD hud;

	// Shaders
	Shader blockShader;
	// Texture Sheets
	TextureSheet blocksSheet;
	// Materials
	Material blockMaterial;

	std::list<std::unique_ptr<Object>> objects;
public:
	Renderer();
	GLFWwindow* initWindow();

	bool isRunning() { return !glfwWindowShouldClose(window); };
	void addBlock(int ID, const glm::vec3& pos) {objects.push_back(std::make_unique<Block>(blockMaterial,ID,pos));}
	void render();
	void handleEvents();
};

void APIENTRY glDebugCallback(GLenum source, GLenum mType, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam);

