#include "stdafx.h"
#include "Camera.h"
#include "Shader.h"

Camera::Camera(GLFWwindow* window) : window(window) {
	glGenBuffers(1, &UBO);

	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);

	glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO, 0, 2 * sizeof(glm::mat4));

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
		((Camera*)glfwGetWindowUserPointer(window))->updateMousePos(x, y);
	});
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
		if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
			((Camera*)glfwGetWindowUserPointer(window))->enable();
	});

	prevTime = glfwGetTime();
}

void Camera::update() {
	double curTime = glfwGetTime();
	double deltaTime = curTime - prevTime;
	prevTime = curTime;

	 float speed = baseSpeed * deltaTime;

	if(!enabled) return;
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) pos += speed * front;
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) pos -= speed * front;
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) pos -= glm::normalize(glm::cross(front, up)) * speed;
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) pos += glm::normalize(glm::cross(front, up)) * speed;
	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) pos += up * speed;
	if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) pos -= up * speed;

	glm::mat4 view = glm::lookAt(pos, pos + front, up);

	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
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
