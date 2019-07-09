#pragma once

#include "Chunk.h"

class TerrainGenerator {
public:
	virtual std::unique_ptr<Chunk> generateChunk(Chunk::Key key) = 0;
};