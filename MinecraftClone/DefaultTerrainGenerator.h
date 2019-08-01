#pragma once

#include "TerrainGenerator.h"

#include "PerlinNoise.hpp"

class DefaultTerrainGenerator : public TerrainGenerator {
private:
	siv::PerlinNoise perlin;
public:
	DefaultTerrainGenerator(uint32_t seed);

	std::unique_ptr<Chunk> generateChunk(World* world, Chunk::Key key) override;
};

