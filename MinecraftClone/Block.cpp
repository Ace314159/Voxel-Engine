#include "stdafx.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Block.h"


Block::Block(Material& material, int ID, const glm::vec3& pos) : Object(material, pos), ID(ID) {
	setTexCoords();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ObjectVertex), (void*)(offsetof(ObjectVertex, ObjectVertex::pos)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ObjectVertex), (void*)(offsetof(ObjectVertex, ObjectVertex::texCoord)));
	glEnableVertexAttribArray(1);
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
	Object::render();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(float), GL_UNSIGNED_INT, 0);
}
