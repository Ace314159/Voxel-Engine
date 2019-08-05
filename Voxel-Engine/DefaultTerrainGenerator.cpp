#include "stdafx.h"

#include "DefaultTerrainGenerator.h"
#include "World.h"

DefaultTerrainGenerator::DefaultTerrainGenerator(uint32_t seed) : perlin(seed) {}

std::unique_ptr<Chunk> DefaultTerrainGenerator::generateChunk(World* world, Chunk::Key key) {
	std::vector<Block> blocks;
	blocks.reserve(CHUNK_VOLUME);

	for(int z = 0; z < CHUNK_Z_LEN; z++) {
		int worldZ = world->getWorldCoord(key.z, z, CHUNK_Z_LEN);
		for(int x = 0; x < CHUNK_X_LEN; x++) {
			int worldX = world->getWorldCoord(key.x, x, CHUNK_X_LEN);

			double perlinX = key.x + (double)x / CHUNK_X_LEN;

			double perlinZ = key.z + (double)z / CHUNK_Z_LEN;

			double e = perlin.octaveNoise0_1(perlinX / freq, perlinZ / freq, numOctaves);
			int elevation = abs((int)round(pow(e, exponent) * CHUNK_Y_LEN));
			for(int y = 0; y < elevation; y++) {
				blocks.emplace_back(BlockTypes::Dirt, glm::vec3(worldX, y, worldZ));
			}
			blocks.emplace_back(BlockTypes::Grass, glm::vec3(worldX, elevation, worldZ));
			for(int y = elevation + 1; y < CHUNK_Y_LEN; y++) {
				blocks.emplace_back(BlockTypes::Air, glm::vec3(worldX, y, worldZ));
			}
		}
	}
	return std::make_unique<Chunk>(world, blocks);
};