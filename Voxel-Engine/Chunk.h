#pragma once

#include "CubeMesh.h"
#include "Block.h"

class World;

class Chunk {
public:
	struct Key {
		int x, z;

		bool operator==(const Key& k) const { return k.x == x && k.z == z; };
		bool operator!=(const Key& k) const { return k.x != x || k.z != z; };
		Key& operator+=(const Key& k) { x += k.x; z += k.z; return *this; };
	};
private:
	CubeMesh mesh;
	bool _canRender = false;
	World* world;
	Chunk::Key key;

	std::vector<Block> blocks;
	std::vector<float> lightMap;
public:
	Chunk(World* world, const std::vector<Block>& blocks, Chunk::Key key);

	static size_t getArrIndex(unsigned int x, unsigned int y, unsigned int z) {
		return CHUNK_LEN * CHUNK_HEIGHT * z + CHUNK_HEIGHT * x + y;
	}

	void makeLightMap();
	void makeMesh();
	void render() const;
	const BlockType& getBlock(unsigned int x, unsigned int y, unsigned int z) const;
	void setBlock(unsigned int x, unsigned int y, unsigned int z, const BlockType& block);
	float getLightLevel(unsigned int x, unsigned int y, unsigned z);
	void setLightLevel(unsigned int x, unsigned int y, unsigned z, float lightLevel);
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

