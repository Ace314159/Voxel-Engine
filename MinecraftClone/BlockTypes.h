#include "Block.h"

struct BlockType {
	const std::string& name;
	unsigned int ID;
	unsigned int texIDs[6]; // Front Right Back Left Top Bottom
	bool isTransparent;

	bool operator==(const BlockType& type) const {
		return ID == type.ID;
	}

	bool operator!=(const BlockType& type) const {
		return ID != type.ID;
	}
};

namespace BlockTypes {
	const BlockType Air = {
		"Air",
		0,
		{0, 0, 0, 0, 0, 0},
		true,
	};

	const BlockType Dirt = {
		"Dirt",
		1,
		{0, 0, 0, 0, 0, 0},
		false,
	};

	const BlockType Grass = {
		"Grass",
		2,
		{2, 2, 2, 2, 1, 0},
		false,
	};
}
