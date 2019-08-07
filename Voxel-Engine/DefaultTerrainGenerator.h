#pragma once

#include "TerrainGenerator.h"

#include "PerlinNoise.hpp"

class DefaultTerrainGenerator : public TerrainGenerator {
private:
	siv::PerlinNoise perlin;

	const int STONE_Y = 20;
	double freq = 5;
	int32_t numOctaves = 5;
	double exponent = 0.75;
public:
	DefaultTerrainGenerator(uint32_t seed);

	std::unique_ptr<Chunk> generateChunk(World* world, Chunk::Key key) override;
};

