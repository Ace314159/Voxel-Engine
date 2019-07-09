#pragma once

#include "Chunk.h"
#include "Shader.h"
#include "FlatTerrainGenerator.h"
#include "TextureAtlas.h"

class World {
private:
	GLuint VAO;

	std::unique_ptr<TerrainGenerator> terrainGenerator = std::make_unique<FlatTerrainGenerator>();

	Shader shader;
	TextureAtlas blockAtlas;
public:
	World();
	std::unordered_map<Chunk::Key, std::unique_ptr<Chunk>> chunks;

	void generateChunks();
	void render();
	const BlockType& getBlock(int x, int y, int z) const;
};

