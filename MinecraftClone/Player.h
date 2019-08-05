#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Entity.h"
#include "World.h"


class Player : public Entity {
private:
	World* world;
	GLFWwindow* window;
	Camera camera;

	bool enabled = true;
	double prevTime;

	const double baseSpeed = 10;
public:
	Player(World* world, GLFWwindow* window, const TextureAtlas& entityAtlas);

	void update();
	void enable() { enabled = true; camera.enable(); }
	void disable() { enabled = false; camera.disable(); };
	void updateMousePos(double x, double y) { camera.updateMousePos(x, y); };
};

