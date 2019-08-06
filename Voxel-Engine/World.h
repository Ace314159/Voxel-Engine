#pragma once

#include "Chunk.h"
#include "Shader.h"
#include "DefaultTerrainGenerator.h"
#include "FlatTerrainGenerator.h"
#include "TextureAtlas.h"

class World {
private:
	GLuint VAO;

	std::unique_ptr<TerrainGenerator> terrainGenerator = std::make_unique<DefaultTerrainGenerator>(123);

	Shader shader;
	TextureAtlas blockAtlas;

	const int RENDER_DISTANCE = 5;
public:
	World();
	std::unordered_map<Chunk::Key, std::unique_ptr<Chunk>> chunks;

	int getChunkCoord(int worldCoord, int chunkCoordLen) const {
		if(worldCoord < 0) return (worldCoord + 1) / chunkCoordLen - 1;
		else return worldCoord / chunkCoordLen;
	};
	int getWorldCoord(int chunkCoord, int blockCoord, int chunkCoordLen) const {
		return chunkCoord * chunkCoordLen + blockCoord;
	}
	int getBlockCoord(int worldCoord, int chunkCoord, int chunkCoordLen) const {
		return worldCoord - chunkCoord * chunkCoordLen;
	}

	bool generatingChunks = true;
	int generatingChunkX = -RENDER_DISTANCE;
	int generatingChunkZ = -RENDER_DISTANCE;

	void generateChunk();
	void render();
	const BlockType& getBlock(int x, int y, int z) const;
	void setBlock(int x, int y, int z, const BlockType& block);
};

