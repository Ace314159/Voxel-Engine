#pragma once

#include "TerrainGenerator.h"

class FlatTerrainGenerator : public TerrainGenerator {
public:
	std::unique_ptr<Chunk> generateChunk(World* world, Chunk::Key key) override;
};

