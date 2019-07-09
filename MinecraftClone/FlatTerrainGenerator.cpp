#include "stdafx.h"

#include "FlatTerrainGenerator.h"

std::unique_ptr<Chunk> FlatTerrainGenerator::generateChunk(World* world, Chunk::Key key) {
	std::vector<Block> blocks;
	const BlockType* blockType;
	for(int y = 0; y < CHUNK_Y_LEN; y++) {
		if(y < 3) blockType = &BlockTypes::Dirt;
		else if(y == 3) blockType = &BlockTypes::Grass;
		else blockType = &BlockTypes::Air;

		for(int x = 0; x < CHUNK_X_LEN; x++) {
			for(int z = 0; z < CHUNK_Z_LEN; z++) {
				blocks.emplace_back(*blockType, glm::vec3(key.x * CHUNK_X_LEN + x, y, key.z * CHUNK_Z_LEN + z));
			}
		}
	}
	return std::make_unique<Chunk>(world, blocks);
};
