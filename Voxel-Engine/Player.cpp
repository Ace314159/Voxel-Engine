#include "stdafx.h"

#include "Player.h"


Player::Player(World* world, GLFWwindow* window) : camera(window), world(world), window(window) {
	camera.enable();
	pos = {0.5, world->chunks[{0, 0}]->getMaxHeight(0, 0) + 1, 0.5};

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
		if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			Player* player = (Player*)glfwGetWindowUserPointer(window);
			if(player->isEnabled()) player->clicked();
			else player->enable();
		}
	});
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
		((Player*)glfwGetWindowUserPointer(window))->updateMousePos(x, y);
	});


	glm::vec4 rayClip = {0, 0, -1, 1}; // Mouse is always centered at (0, 0) NDC
	rayEye = glm::inverse(camera.projection) * rayClip;
	rayEye = {rayEye.x, rayEye.y, -1, 0};

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
		glm::ivec3 checkPos(floor(newPos.x), floor(newPos.y), floor(newPos.z));
		
		if(world->getBlock(checkPos.x, checkPos.y, checkPos.z) == BlockTypes::Air &&
			world->getBlock(checkPos.x, checkPos.y + 1, checkPos.z) == BlockTypes::Air) {
			pos[i] += dPos[i];
		}
	}

	cameraPos = pos + glm::vec3(0, 1.5, 0);
	camera.update(cameraPos);
}

void Player::clicked() {
	glm::vec3 rayWorld = glm::inverse(camera.view) * rayEye;
	rayWorld = glm::normalize(rayWorld);

	for(float i = 1; i < reach; i += 0.01f) {
		glm::ivec3 check = cameraPos + rayWorld * i;
		if(world->getBlock(check.x, check.y, check.z) != BlockTypes::Air) {
			world->setBlock(check.x, check.y, check.z, BlockTypes::Air);
			break;
		}
	}
}
