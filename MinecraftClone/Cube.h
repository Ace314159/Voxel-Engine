#pragma once

#include "Object.h"

class Cube : public Object {
private:
	GLuint VAO, VBO, EBO;

	float vertices[6 * 4 * 3] = {
		-0.5f, -0.5f,  0.5f, // Front
		 0.5f, -0.5f,  0.5f, // Front
		 0.5f,  0.5f,  0.5f, // Front
		-0.5f,  0.5f,  0.5f, // Front
		 0.5f,  0.5f,  0.5f, // Right
		 0.5f,  0.5f, -0.5f, // Right
		 0.5f, -0.5f, -0.5f, // Right
		 0.5f, -0.5f,  0.5f, // Right
		-0.5f, -0.5f, -0.5f, // Back
		 0.5f, -0.5f, -0.5f, // Back
		 0.5f,  0.5f, -0.5f, // Back
		-0.5f,  0.5f, -0.5f, // Back
		-0.5f, -0.5f, -0.5f, // Left
		-0.5f, -0.5f,  0.5f, // Left
		-0.5f,  0.5f,  0.5f, // Left
		-0.5f,  0.5f, -0.5f, // Left
		 0.5f,  0.5f,  0.5f, // Top
		-0.5f,  0.5f,  0.5f, // Top
		-0.5f,  0.5f, -0.5f, // Top
		 0.5f,  0.5f, -0.5f, // Top
		-0.5f, -0.5f, -0.5f, // Bottom
		 0.5f, -0.5f, -0.5f, // Bottom
		 0.5f, -0.5f,  0.5f, // Bottom
		-0.5f, -0.5f,  0.5f  // Bottom
	};

	GLuint indices[6 * 3 * 2] = {
		0,   1,  2,  0,  2,  3, // Front
		4,   5,  6,  4,  6,  7, // Right
		8,   9, 10,  8, 10, 11, // Back
		12, 13, 14, 12, 14, 15, // Left
		16, 17, 18, 16, 18, 19, // Top
		20, 21, 22, 20, 22, 23  // Bottom
	};
public:
	Cube(const Shader& shader, float x, float y, float z);

	void render() override;
};

