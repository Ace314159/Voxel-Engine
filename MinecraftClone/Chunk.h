#pragma once

#include "Mesh.h"
#include "Block.h"

class World;

class Chunk {
private:
	Mesh mesh;

	std::vector<Block> blocks;
public:
	Chunk(const std::vector<Block>& blocks);

	static size_t getArrIndex(unsigned int x, unsigned int y, unsigned int z) { 
		return CHUNK_X_LEN * CHUNK_Z_LEN * y + CHUNK_X_LEN * z + x;
	}

	struct Key {
		int x, z;

		bool operator==(const Key& k) const { return k.x == x && k.z == z; };
	};

	void makeMesh(World* world);
	void render() const;
	const BlockType& getBlock(unsigned int x, unsigned int y, unsigned int z) const;
};

namespace std {
	template<>
	struct hash<Chunk::Key> {
		std::size_t operator()(const Chunk::Key& k) const {
			return (k.x + k.z)* (k.x + k.z + 1) / 2 + k.z; // Cantor Tuple Function
		}
	};
}
