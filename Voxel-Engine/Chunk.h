#pragma once

#include "CubeMesh.h"
#include "Block.h"

class World;

class Chunk {
private:
	CubeMesh mesh;
	bool _canRender = false;
	World* world;

	std::vector<Block> blocks;
public:
	Chunk(World* world, const std::vector<Block>& blocks);

	static size_t getArrIndex(unsigned int x, unsigned int y, unsigned int z) { 
		return CHUNK_LEN * CHUNK_HEIGHT * z + CHUNK_HEIGHT * x + y;
	}

	struct Key {
		int x, z;

		bool operator==(const Key& k) const { return k.x == x && k.z == z; };
		bool operator!=(const Key& k) const { return k.x != x || k.z != z; };
		Key& operator+=(const Key& k) { x += k.x; z += k.z; return *this; };
	};

	void makeMesh();
	void render() const;
	const BlockType& getBlock(unsigned int x, unsigned int y, unsigned int z) const;
	void setBlock(unsigned int x, unsigned int y, unsigned int z, const BlockType& block);
	bool canRender() const { return _canRender; };
	unsigned int getMaxHeight(unsigned int x, unsigned int z);
};

namespace std {
	template<>
	struct hash<Chunk::Key> {
		std::size_t operator()(const Chunk::Key& k) const {
			return (k.x + k.z)* (k.x + k.z + 1) / 2 + k.z; // Cantor Tuple Function
		}
	};
}

