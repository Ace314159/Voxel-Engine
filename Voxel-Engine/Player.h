#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "World.h"


class Player {
private:
	World* world;
	GLFWwindow* window;
	Camera camera;

	bool enabled = true;
	double prevTime;

	glm::vec3 pos;
	const double baseSpeed = 10;
	const float reach = 5;
	const float buffer = 0.2f;
	glm::vec4 rayEye;
	glm::vec3 cameraPos;
public:
	Player(World* world, GLFWwindow* window);

	void update();
	bool isEnabled() const { return enabled; };
	const glm::vec3& getPos() const { return pos; };
	void enable() { enabled = true; camera.enable(); }
	void disable() { enabled = false; camera.disable(); };
	void updateMousePos(double x, double y) { camera.updateMousePos(x, y); };
	void clicked();
};

