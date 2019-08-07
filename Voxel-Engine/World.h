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

	bool generatingChunks = true;
	Chunk::Key prevPlayerChunk = {0, 0};
	Chunk::Key generatingChunk = {0, 0};
	Chunk::Key generatingChunkIncrements[4] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
	int generatingChunkIndex = 0;
	const int RENDER_DISTANCE = 5;

	void getNextChunkToGen();
public:
	World();
	std::unordered_map<Chunk::Key, std::unique_ptr<Chunk>> chunks;

	int getChunkCoord(int worldCoord) const {
		if(worldCoord < 0) return (worldCoord + 1) / CHUNK_LEN - 1;
		else return worldCoord / CHUNK_LEN;
	};
	int getWorldCoord(int chunkCoord, int blockCoord) const {
		return chunkCoord * CHUNK_LEN + blockCoord;
	}
	int getBlockCoord(int worldCoord, int chunkCoord) const {
		return worldCoord - chunkCoord * CHUNK_LEN;
	}

	void generateChunk(const glm::vec3& playerPos);
	void render() const;
	const BlockType& getBlock(int x, int y, int z) const;
	void setBlock(int x, int y, int z, const BlockType& block);
};

