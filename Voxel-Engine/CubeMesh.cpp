#include "stdafx.h"
#include "CubeMesh.h"

glm::ivec3 CubeMesh::faces[6][4] = {
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

glm::ivec2 CubeMesh::texCoords[4] = {
	{1, 1},
	{0, 1},
	{0, 0},
	{1, 0},
};

glm::ivec3 CubeMesh::adjacentFaces[6] = {
	{0, 0, 1},
	{1, 0, 0},
	{0, 0, -1},
	{-1, 0, 0},
	{0, 1, 0},
	{0, -1, 0},
};

void CubeMesh::addFace(const glm::ivec3& pos, Face type, int textureID, float lightLevel) {
	indices.insert(indices.end(),
		{0 + vertices.size(), 1 + vertices.size(), 2 + vertices.size(),
		 2 + vertices.size(), 3 + vertices.size(), 0 + vertices.size()});
	for(int i = 0; i < 4; i++) {
		vertices.push_back({ faces[(int)type][i] + pos, glm::ivec3(texCoords[i], textureID), lightLevel });
	}
}
