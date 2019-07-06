#pragma once

#include "Object.h"


class Block : public Object {
private:
	static GLuint VAO, EBO;
	GLuint VBO;

	ObjectVertex vertices[6 * 4] = {
		// Front
		{glm::vec3(0.5,  0.5,  0.5), glm::vec2()},
		{glm::vec3(-0.5,  0.5,  0.5), glm::vec2()},
		{glm::vec3(-0.5, -0.5,  0.5), glm::vec2()},
		{glm::vec3(0.5, -0.5,  0.5), glm::vec2()},
		// Right
		{glm::vec3(0.5,  0.5, -0.5), glm::vec2()},
		{glm::vec3(0.5,  0.5,  0.5), glm::vec2()},
		{glm::vec3(0.5, -0.5,  0.5), glm::vec2()},
		{glm::vec3(0.5, -0.5, -0.5), glm::vec2()},
		// Back
		{glm::vec3(-0.5,  0.5, -0.5), glm::vec2()},
		{glm::vec3(0.5,  0.5, -0.5), glm::vec2()},
		{glm::vec3(0.5, -0.5, -0.5), glm::vec2()},
		{glm::vec3(-0.5, -0.5, -0.5), glm::vec2()},
		// Left
		{glm::vec3(-0.5,  0.5,  0.5), glm::vec2()},
		{glm::vec3(-0.5,  0.5, -0.5), glm::vec2()},
		{glm::vec3(-0.5, -0.5, -0.5), glm::vec2()},
		{glm::vec3(-0.5, -0.5,  0.5), glm::vec2()},
		// Top
		{glm::vec3(0.5,  0.5, -0.5), glm::vec2()},
		{glm::vec3(-0.5,  0.5, -0.5), glm::vec2()},
		{glm::vec3(-0.5,  0.5,  0.5), glm::vec2()},
		{glm::vec3(0.5,  0.5,  0.5), glm::vec2()},
		// Bottom
		{glm::vec3(0.5, -0.5,  0.5), glm::vec2()},
		{glm::vec3(-0.5, -0.5,  0.5), glm::vec2()},
		{glm::vec3(-0.5, -0.5, -0.5), glm::vec2()},
		{glm::vec3(0.5, -0.5, -0.5), glm::vec2()},
	};

	static GLuint indices[6 * 3 * 2];

	int ID;
	void setTexCoords();
	void setTexCoords(int frontID, int rightID, int backID, int leftID, int topID, int bottomID);
public:
	Block(Material& shader, int ID, const glm::vec3& pos);

	void render() override;

	static void init();
};

