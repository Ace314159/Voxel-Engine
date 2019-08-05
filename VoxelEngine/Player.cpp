#include "stdafx.h"

#include "Player.h"


Player::Player(World* world, GLFWwindow* window, const TextureAtlas& entityAtlas) : 
	Entity({1, 2, 1}, 0, entityAtlas), camera(window), world(world), window(window) {
	camera.enable();
	pos = {0.5, world->chunks[{0, 0}]->getMaxHeight(0, 0) + 10, 0.5};

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
		if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
			((Player*)glfwGetWindowUserPointer(window))->enable();
	});
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
		((Player*)glfwGetWindowUserPointer(window))->updateMousePos(x, y);
	});

	prevTime = glfwGetTime();
}

void Player::update() {
	if(!enabled) return;

	double curTime = glfwGetTime();
	double deltaTime = curTime - prevTime;
	prevTime = curTime;

	float speed = float(baseSpeed * deltaTime);

	glm::vec3 dPos(0, 0, 0);
	glm::vec3 front0Y = glm::normalize(glm::vec3(camera.front.x, 0, camera.front.z));
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) dPos += front0Y * speed;
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) dPos -= front0Y * speed;
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
		dPos -= glm::normalize(glm::cross(front0Y, camera.up)) * speed;
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
		dPos += glm::normalize(glm::cross(front0Y, camera.up)) * speed;
	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		dPos += camera.up * speed;
	if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) dPos -= camera.up * speed;

	for(int i = 0; i < 3; i++) {
		glm::vec3 newPos = pos;
		newPos[i] += dPos[i];
		if(newPos.x < 0) newPos.x--;
		if(newPos.y < 0) newPos.y--;
		if(newPos.z < 0) newPos.z--;
		glm::ivec3 checkPos(newPos.x, newPos.y, newPos.z);
		
		if(world->getBlock(checkPos.x, checkPos.y, checkPos.z) == BlockTypes::Air &&
			world->getBlock(checkPos.x, checkPos.y + 1, checkPos.z) == BlockTypes::Air) {
			pos[i] += dPos[i];
		}
	}

	std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;

	camera.update(pos + glm::vec3(0, 1.5, 0));
}
