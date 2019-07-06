#pragma once

#include "Object.h"


class Block : public Object {
private:
	GLuint VAO, VBO, EBO;

	ObjectVertex vertices[6 * 4] = {
		// Front
		{glm::vec3( 0.5,  0.5,  0.5), glm::vec2()},
		{glm::vec3(-0.5,  0.5,  0.5), glm::vec2()},
		{glm::vec3(-0.5, -0.5,  0.5), glm::vec2()},
		{glm::vec3( 0.5, -0.5,  0.5), glm::vec2()},
		// Right
		{glm::vec3( 0.5,  0.5, -0.5), glm::vec2()},
		{glm::vec3( 0.5,  0.5,  0.5), glm::vec2()},
		{glm::vec3( 0.5, -0.5,  0.5), glm::vec2()},
		{glm::vec3( 0.5, -0.5, -0.5), glm::vec2()},
		// Back
		{glm::vec3(-0.5,  0.5, -0.5), glm::vec2()},
		{glm::vec3( 0.5,  0.5, -0.5), glm::vec2()},
		{glm::vec3( 0.5, -0.5, -0.5), glm::vec2()},
		{glm::vec3(-0.5, -0.5, -0.5), glm::vec2()},
		// Left
		{glm::vec3(-0.5,  0.5,  0.5), glm::vec2()},
		{glm::vec3(-0.5,  0.5, -0.5), glm::vec2()},
		{glm::vec3(-0.5, -0.5, -0.5), glm::vec2()},
		{glm::vec3(-0.5, -0.5,  0.5), glm::vec2()},
		// Top
		{glm::vec3( 0.5,  0.5, -0.5), glm::vec2()},
		{glm::vec3(-0.5,  0.5, -0.5), glm::vec2()},
		{glm::vec3(-0.5,  0.5,  0.5), glm::vec2()},
		{glm::vec3( 0.5,  0.5,  0.5), glm::vec2()},
		// Bottom
		{glm::vec3( 0.5, -0.5,  0.5), glm::vec2()},
		{glm::vec3(-0.5, -0.5,  0.5), glm::vec2()},
		{glm::vec3(-0.5, -0.5, -0.5), glm::vec2()},
		{glm::vec3( 0.5, -0.5, -0.5), glm::vec2()},
	};

	GLuint indices[6 * 3 * 2] = {
		 0,  1,  2,  2,  3,  0, // Front
		 4,  5,  6,  6,  7,  4, // Right
		 8,  9, 10, 10, 11,  8, // Back
		12, 13, 14, 14, 15, 12, // Left
		16, 17, 18, 18, 19, 16, // Top
		20, 21, 22, 22, 23, 20, // Bottom
	};

	int ID;
	void setTexCoords();
	void setTexCoords(int frontID, int rightID, int backID, int leftID, int topID, int bottomID);
public:
	Block(Material& shader, int ID, const glm::vec3& pos);

	void render() override;
};

