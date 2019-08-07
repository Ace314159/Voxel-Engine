#include "stdafx.h"

#include "FlatTerrainGenerator.h"
#include "World.h"

std::unique_ptr<Chunk> FlatTerrainGenerator::generateChunk(World* world, Chunk::Key key) {
	std::vector<Block> blocks;

	for(int z = 0; z < CHUNK_LEN; z++) {
		int worldZ = world->getWorldCoord(key.z, z);
		for(int x = 0; x < CHUNK_LEN; x++) {
			int worldX = world->getWorldCoord(key.x, x);
			for(int y = 0; y < GRASS_Y; y++) blocks.emplace_back(BlockTypes::Dirt, glm::vec3(worldX, y, worldZ));
			blocks.emplace_back(BlockTypes::Grass, glm::vec3(worldX, GRASS_Y, worldZ));
			for(int y = GRASS_Y + 1; y < CHUNK_HEIGHT; y++)
				blocks.emplace_back(BlockTypes::Air, glm::vec3(worldX, y, worldZ));
		}
	}
	return std::make_unique<Chunk>(world, blocks);
};
