#include "stdafx.h"

#include "DefaultTerrainGenerator.h"
#include "World.h"
#include "Biomes.h"

DefaultTerrainGenerator::DefaultTerrainGenerator(uint32_t seed) { eNoise.setSeed(seed); mNoise.setSeed(seed ^ 2432447131); }

std::unique_ptr<Chunk> DefaultTerrainGenerator::generateChunk(World* world, Chunk::Key key) {
	std::vector<Block> blocks;
	blocks.reserve(CHUNK_VOLUME);

	for(int z = 0; z < CHUNK_LEN; z++) {
		int worldZ = world->getWorldCoord(key.z, z);
		for(int x = 0; x < CHUNK_LEN; x++) {
			int worldX = world->getWorldCoord(key.x, x);

			double perlinX = key.x + (double)x / CHUNK_LEN;
			double perlinZ = key.z + (double)z / CHUNK_LEN;

			double e = eNoise.get(perlinX, perlinZ);
			double m = mNoise.get(perlinX, perlinZ);

			Biomes::getBiome(e, m)->generateColumn(blocks, e, worldX, worldZ);
		}
	}
	assert(blocks.size() == CHUNK_VOLUME);
	return std::make_unique<Chunk>(world, blocks);
};
