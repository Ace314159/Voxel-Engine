#pragma once

#include "TerrainGenerator.h"

class FlatTerrainGenerator : public TerrainGenerator {
private:
	const int GRASS_Y = 5;
	const int STONE_Y = 3;
public:
	std::unique_ptr<Chunk> generateChunk(World* world, Chunk::Key key) override;
};

