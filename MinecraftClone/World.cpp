#include "stdafx.h"

#include "World.h"

World::World() : shader("block"), blockAtlas("blocks.png") {
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, offsetof(Mesh::Vertex, Mesh::Vertex::pos));
	glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, offsetof(Mesh::Vertex, Mesh::Vertex::texCoord));

	glVertexAttribBinding(0, 0);
	glVertexAttribBinding(1, 0);

	// UBO Setup for Shader
	glUniformBlockBinding(shader.ID, glGetUniformBlockIndex(shader.ID, "Camera"), 0);

}

void World::generateChunk() {
	int x = generatingChunkX;
	int z = generatingChunkZ;

	Chunk::Key key;
	key = {x - 1, z + 0};
	if(chunks.find(key) == chunks.end())
		chunks.try_emplace(key, std::move(terrainGenerator->generateChunk(this, key)));
	key = {x + 1, z + 0};
	if(chunks.find(key) == chunks.end())
		chunks.try_emplace(key, std::move(terrainGenerator->generateChunk(this, key)));
	key = {x + 0, z - 1};
	if(chunks.find(key) == chunks.end())
		chunks.try_emplace(key, std::move(terrainGenerator->generateChunk(this, key)));
	key = {x + 0, z + 1};
	if(chunks.find(key) == chunks.end())
		chunks.try_emplace(key, std::move(terrainGenerator->generateChunk(this, key)));
	key = {x + 0, z + 0};
	if(chunks.find(key) == chunks.end())
		chunks.try_emplace(key, std::move(terrainGenerator->generateChunk(this, key)));

	chunks[key]->makeMesh(this);

	if(++generatingChunkX > RENDER_DISTANCE) {
		generatingChunkX = -RENDER_DISTANCE;
		if(++generatingChunkZ > RENDER_DISTANCE) generatingChunks = false;
	}
}

void World::render() {
	glBindVertexArray(VAO);
	shader.use();
	blockAtlas.use();
	shader.setInt("tex", blockAtlas.unit);

	for(const auto& kv : chunks) {
		kv.second->render();
	}
}

const BlockType& World::getBlock(int x, int y, int z) const {
	int chunkX = getChunkCoord(x, CHUNK_X_LEN);
	int chunkZ = getChunkCoord(z, CHUNK_Z_LEN);

	if(chunks.find({chunkX, chunkZ}) == chunks.end()) throw std::runtime_error("Block doesn't exist!");
	if(y >= CHUNK_Y_LEN || y < 0) return BlockTypes::Air;

	int blockX = getBlockCoord(x, chunkX, CHUNK_X_LEN);
	int blockZ = getBlockCoord(z, chunkZ, CHUNK_Z_LEN);

	return chunks.at({chunkX, chunkZ})->getBlock(blockX, y, blockZ);
}
