#pragma once

#include "Mesh.h"

class CubeMesh : public Mesh {
private:
	static glm::ivec3 faces[6][4];
	static glm::ivec2 texCoords[4];
public:
	enum class Face { FRONT = 0, RIGHT = 1, BACK = 2, LEFT = 3, TOP = 4, BOTTOM = 5 };
	static glm::ivec3 adjacentFaces[6];

	void addFace(const glm::ivec3& pos, Face type, int textureID, float lightLevel);
};

