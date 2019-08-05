#pragma once

#include <glm/glm.hpp>

#include "BlockTypes.h"

class Block {
public:
	const BlockType& type;
	glm::vec3 pos;

	Block(const BlockType& type, const glm::vec3& pos) : type(type), pos(pos) {};
};