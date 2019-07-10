#include "stdafx.h"

#include "Mesh.h"

glm::vec3 Mesh::faces[6][4] = {
	// Front
	{{1, 1, 1},
	{0, 1, 1},
	{0, 0, 1},
	{1, 0, 1}},
	// Right
	{{1, 1, 0},
	{1, 1, 1},
	{1, 0, 1},
	{1, 0, 0}},
	// Back
	{{0, 1, 0},
	{1, 1, 0},
	{1, 0, 0},
	{0, 0, 0}},
	// Left
	{{0, 1, 1},
	{0, 1, 0},
	{0, 0, 0},
	{0, 0, 1}},
	// Top
	{{1, 1, 0},
	{0, 1, 0},
	{0, 1, 1},
	{1, 1, 1}},
	// Bottom
	{{1, 0, 1},
	{0, 0, 1},
	{0, 0, 0},
	{1, 0, 0}},
};
glm::vec2 Mesh::texCoords[4] = {
	{1, 1},
	{0, 1},
	{0, 0},
	{1, 0},
};
glm::vec3 Mesh::adjacentFaces[6] = {
	{0, 0, 1},
	{1, 0, 0},
	{0, 0, -1},
	{-1, 0, 0},
	{0, 1, 0},
	{0, -1, 0},
};

Mesh::Mesh() {
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

Mesh::~Mesh() {
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::addFace(const glm::vec3& pos, Face type, int textureID) {
	indices.insert(indices.end(),
		{0 + vertices.size(), 1 + vertices.size(), 2 + vertices.size(),
		 2 + vertices.size(), 3 + vertices.size(), 0 + vertices.size()});
	for(int i = 0; i < 4; i++) {
		vertices.push_back({faces[(int)type][i] + pos, glm::vec3(texCoords[i], textureID)});
	}
}

void Mesh::buffer() {
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void Mesh::clear() {
	vertices.clear();
	indices.clear();
}

void Mesh::render() const {
	glBindVertexBuffer(0, VBO, 0, sizeof(Vertex));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
