#include "stdafx.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Shader.h"
#include "World.h"

Camera::Camera(GLFWwindow* window) : window(window) {
	glGenBuffers(1, &UBO);

	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));


	glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO, 0, 2 * sizeof(glm::mat4));
}

void Camera::update(const glm::vec3& pos) {
	view = glm::lookAt(pos, pos + front, up);

	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
}

void Camera::updateMousePos(double x, double y) {
	double dX = (x - prevX) * sensitivity;
	double dY = -(y - prevY) * sensitivity; // Negative since y values increase from top to bottom
	prevX = x;
	prevY = y;
	if(!enabled) return;

	yaw += dX;
	pitch += dY;
	if(pitch > 89) pitch = 89;
	else if(pitch < -89) pitch = -89;

	front = glm::normalize(glm::vec3(
		cos(glm::radians(pitch)) * cos(glm::radians(yaw)),
		sin(glm::radians(pitch)),
		cos(glm::radians(pitch)) * sin(glm::radians(yaw))
	));
}
