#include "stdafx.h"

#include "FlatTerrainGenerator.h"

std::unique_ptr<Chunk> FlatTerrainGenerator::generateChunk(World* world, Chunk::Key key) {
	std::vector<Block> blocks;

	for(int z = 0; z < CHUNK_Z_LEN; z++) {
		int worldZ = key.z * CHUNK_Z_LEN + z;
		for(int x = 0; x < CHUNK_X_LEN; x++) {
			int worldX = key.x * CHUNK_X_LEN + x;
			for(int y = 0; y < GRASS_Y; y++) blocks.emplace_back(BlockTypes::Dirt, glm::vec3(worldX, y, worldZ));
			blocks.emplace_back(BlockTypes::Grass, glm::vec3(worldX, GRASS_Y, worldZ));
			for(int y = GRASS_Y + 1; y < CHUNK_Y_LEN; y++)
				blocks.emplace_back(BlockTypes::Air, glm::vec3(worldX, y, worldZ));
		}
	}
	return std::make_unique<Chunk>(world, blocks);
};
