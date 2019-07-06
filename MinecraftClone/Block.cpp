#include "stdafx.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Block.h"

GLuint Block::VAO;
GLuint Block::EBO;

GLuint Block::indices[6 * 3 * 2] = {
		 0,  1,  2,  2,  3,  0, // Front
		 4,  5,  6,  6,  7,  4, // Right
		 8,  9, 10, 10, 11,  8, // Back
		12, 13, 14, 14, 15, 12, // Left
		16, 17, 18, 18, 19, 16, // Top
		20, 21, 22, 22, 23, 20, // Bottom
};

void Block::init() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0);
	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, offsetof(ObjectVertex, ObjectVertex::pos));
	glVertexAttribBinding(0, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, offsetof(ObjectVertex, ObjectVertex::texCoord));
	glVertexAttribBinding(1, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
}

Block::Block(Material& material, int ID, const glm::vec3& pos) : Object(material, pos), ID(ID) {
	setTexCoords();

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
}

void Block::setTexCoords() {
	switch(ID) {
	case 0: // Dirt Block
		setTexCoords(0, 0, 0, 0, 1, 0);
		break;
	default:
		throw std::runtime_error("Invalid Block ID " + ID);
	}
}

void Block::setTexCoords(int frontID, int rightID, int backID, int leftID, int topID, int bottomID) {
	material.texSheet.setTexCoords(frontID, &vertices[0]);
	material.texSheet.setTexCoords(rightID, &vertices[4]);
	material.texSheet.setTexCoords(backID, &vertices[8]);
	material.texSheet.setTexCoords(leftID, &vertices[12]);
	material.texSheet.setTexCoords(topID, &vertices[16]);
	material.texSheet.setTexCoords(bottomID, &vertices[20]);
}

void Block::render() {
	useMaterial();
	glBindVertexArray(VAO);
	glBindVertexBuffer(0, VBO, 0, sizeof(ObjectVertex));
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
}
