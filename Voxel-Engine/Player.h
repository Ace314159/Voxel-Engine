#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "OutlinedCubeMesh.h"
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

	OutlinedCubeMesh selectedBlockMesh;
	glm::ivec3 selectedBlockCoords;
	void setSelectedBlock();

	const double gravity = -30;
	const double jumpVel = 10;
	const double maxYVel = 10;
	double yVel = 0;
	double prevJumpTime = -10;
	bool prevJumped = false;
	double maxFlyDelay = 0.3;
	bool flying = false;
public:
	Player(World* world, GLFWwindow* window);

	void update();
	void render();
	bool isEnabled() const { return enabled; };
	const glm::vec3& getPos() const { return pos; };
	void enable() { enabled = true; camera.enable(); }
	void disable() { enabled = false; camera.disable(); };
	void updateMousePos(double x, double y) { camera.updateMousePos(x, y); };
	void clicked();
};

