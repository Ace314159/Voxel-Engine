#pragma once

#include "Noise.h"
#include "TerrainGenerator.h"

class DefaultTerrainGenerator : public TerrainGenerator {
private:
	Noise eNoise = Noise(5, 5, 0.75);
	Noise mNoise = Noise(10, 1, 1);
public:
	DefaultTerrainGenerator(uint32_t seed);

	std::unique_ptr<Chunk> generateChunk(World* world, Chunk::Key key) override;
};

