#pragma once

#include "Chunk.h"

class TerrainGenerator {
public:
	virtual std::unique_ptr<Chunk> generateChunk(World* world, Chunk::Key key) = 0;
};