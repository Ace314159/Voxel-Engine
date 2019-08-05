#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class World;

class Camera {
private:
	GLFWwindow* window;

	GLuint UBO;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / SCREEN_HEIGHT,
		0.0001f, 1000.0f);
	// Makes View Matrix
	glm::vec3 front;
	const glm::vec3 up{0, 1, 0};

	const double baseSpeed = 10;
	const double sensitivity = 0.1;

	double yaw = -90;
	double pitch = 0;
	double prevX = SCREEN_WIDTH / 2, prevY = SCREEN_HEIGHT / 2;
	double enabled = true;
public:
	Camera(GLFWwindow* window);

	void update(const glm::vec3& pos);
	void updateMousePos(double x, double y);
	void enable() { enabled = true; glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); };
	void disable() { enabled = false; glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); };

	friend class Player;
};

