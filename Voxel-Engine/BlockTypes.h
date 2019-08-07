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

	const BlockType Stone = {
		"Stone",
		3,
		{3, 3, 3, 3, 3, 3},
		false,
	};

	const BlockType Sand = {
		"Sand",
		4,
		{4, 4, 4, 4, 4, 4},
		false,
	};

	const BlockType Water = {
		"Water",
		5,
		{5, 5, 5, 5, 5, 5},
		true,
	};

	const BlockType Snow = {
		"Snow",
		6,
		{6, 6, 6, 6, 6, 6},
		false,
	};
}
