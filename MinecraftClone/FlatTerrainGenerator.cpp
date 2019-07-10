#include "stdafx.h"

#include "FlatTerrainGenerator.h"

std::unique_ptr<Chunk> FlatTerrainGenerator::generateChunk(World* world, Chunk::Key key) {
	std::vector<Block> blocks;
	const BlockType* blockType;
	for(int y = 0; y < CHUNK_Y_LEN; y++) {
		if(y < 3) blockType = &BlockTypes::Dirt;
		else if(y == 3) blockType = &BlockTypes::Grass;
		else blockType = &BlockTypes::Air;

		for(int z = 0; z < CHUNK_Z_LEN; z++) {
			int worldZ = key.z * CHUNK_Z_LEN + z;
			for(int x = 0; x < CHUNK_X_LEN; x++) {
				int worldX = key.x * CHUNK_X_LEN + x;
				blocks.emplace_back(*blockType, glm::vec3(worldX, y, worldZ));
			}
		}
	}
	return std::make_unique<Chunk>(world, blocks);
};
