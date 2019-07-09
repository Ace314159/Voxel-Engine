#pragma once

#include "TerrainGenerator.h"

class FlatTerrainGenerator : public TerrainGenerator {
public:
	std::unique_ptr<Chunk> generateChunk(Chunk::Key key) override;
};

