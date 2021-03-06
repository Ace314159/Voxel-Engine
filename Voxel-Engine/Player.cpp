#include "stdafx.h"

#include "Player.h"

#include <glm/gtx/string_cast.hpp>


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
	
	// Move player from inputs
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


	// Apply Gravity
	bool jumpPressed = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
	if(jumpPressed) {
		if(!prevJumped) {
			if(curTime - prevJumpTime < 0.3) flying = !flying;
			prevJumpTime = curTime;
			prevJumped = true;
		}
	} else prevJumped = false;
	//std::cout << flying << std::endl;
	if(flying) {
		yVel = 0;
		dPos.y = 0;
		if(jumpPressed) dPos += camera.up * speed;
		if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) dPos -= camera.up * speed;
	} else {
		if(yVel == 0 && jumpPressed) yVel = jumpVel;
		yVel += gravity * deltaTime;
		dPos.y = float(yVel * deltaTime);
	}

	// Collision Detection
	for(int i = 0; i < 3; i++) {
		glm::vec3 newPos = pos;
		newPos[i] += dPos[i] + copysign(buffer, dPos[i]);
		glm::ivec3 checkPos(floor(newPos.x), floor(newPos.y), floor(newPos.z));

		if(world->getBlock(checkPos.x, checkPos.y, checkPos.z) == BlockTypes::Air &&
			world->getBlock(checkPos.x, checkPos.y + 1, checkPos.z) == BlockTypes::Air) {
			pos[i] += dPos[i];
		} else if(i == 1) {
			yVel = 0;
			flying = false;
		}
	}

	// Add 1.5 to account for head height
	cameraPos = pos + glm::vec3(0, 1.5, 0);
	camera.update(cameraPos);

	setSelectedBlock();
}

void Player::render() {
	if(selectedBlockCoords.y > 0)
		selectedBlockMesh.render();
}

void Player::setSelectedBlock() {
	glm::vec3 rayWorld = glm::inverse(camera.view) * rayEye;
	rayWorld = glm::normalize(rayWorld);

	selectedBlockCoords.y = -1;
	selectedBlockMesh.clear();
	for(float i = 1; i <= reach; i += 0.01f) {
		glm::ivec3 check = glm::floor(cameraPos + rayWorld * i);
		if(world->getBlock(check.x, check.y, check.z) != BlockTypes::Air) {
			selectedBlockCoords = check;

			for(int i = 0; i < 6; i++) {
				glm::ivec3 adjPos = selectedBlockCoords + (glm::ivec3)CubeMesh::adjacentFaces[i];
				if(world->getBlock(adjPos.x, adjPos.y, adjPos.z).isTransparent)
					selectedBlockMesh.addFace(selectedBlockCoords, (CubeMesh::Face)i, 0, 15);
			}
			selectedBlockMesh.buffer();
			break;
		}
	}
}

void Player::clicked() {
	world->setBlock(selectedBlockCoords.x, selectedBlockCoords.y, selectedBlockCoords.z, BlockTypes::Air);
}
