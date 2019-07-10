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

	generateChunks();
}

void World::generateChunks() {
	chunks.try_emplace({0, 0}, terrainGenerator->generateChunk(this, {0, 0}));
	chunks.try_emplace({-1, 0}, terrainGenerator->generateChunk(this, {-1, 0}));
	chunks.try_emplace({0, -1}, terrainGenerator->generateChunk(this, {0, -1}));
	chunks.try_emplace({-1, -1}, terrainGenerator->generateChunk(this, {-1, -1}));
	chunks[{0, 0}]->makeMesh(this);
	chunks[{-1, 0}]->makeMesh(this);
	chunks[{0, -1}]->makeMesh(this);
	chunks[{-1, -1}]->makeMesh(this);
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
	int chunkX, chunkZ;
	if(x < 0) chunkX = (x + 1) / CHUNK_X_LEN - 1;
	else chunkX = x / CHUNK_X_LEN;
	if(z < 0) chunkZ = (z + 1) / CHUNK_Z_LEN - 1;
	else chunkZ = z / CHUNK_Z_LEN;

	if(chunks.find({chunkX, chunkZ}) == chunks.end() || y >= CHUNK_Y_LEN || y < 0) return BlockTypes::Air;

	if(x < 0) x = CHUNK_X_LEN - (-(x + 1) % CHUNK_X_LEN) - 1;
	else x = x % CHUNK_X_LEN;
	if(z < 0) z = CHUNK_Z_LEN - (-(z + 1) % CHUNK_Z_LEN) - 1;
	else z = abs(z % CHUNK_Z_LEN);

	return chunks.at({chunkX, chunkZ})->getBlock(x, y, z);
}
