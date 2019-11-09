#include "stdafx.h"

#include "World.h"

World::World() : shader("block"), blockAtlas("blocks.png") {
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, offsetof(Mesh::Vertex, Mesh::Vertex::pos));
	glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, offsetof(Mesh::Vertex, Mesh::Vertex::texCoord));
	glVertexAttribFormat(2, 3, GL_FLOAT, GL_FALSE, offsetof(Mesh::Vertex, Mesh::Vertex::normal));

	glVertexAttribBinding(0, 0);
	glVertexAttribBinding(1, 0);
	glVertexAttribBinding(2, 0);

	// UBO Setup for Shader
	glUniformBlockBinding(shader.ID, glGetUniformBlockIndex(shader.ID, "Camera"), 0);

	chunks.try_emplace({0, 0}, std::move(terrainGenerator->generateChunk(this, {0, 0})));
}

void World::getNextChunkToGen() {
	while(chunks.find(generatingChunk) != chunks.end() && chunks[generatingChunk]->canRender()) {
		int xDiff = generatingChunk.x - prevPlayerChunk.x;
		int zDiff = generatingChunk.z - prevPlayerChunk.z;

		if(xDiff == zDiff) {
			if(xDiff >= 0) {
				if(xDiff == RENDER_DISTANCE) {
					generatingChunks = false;
					break;
				} else generatingChunk.x++;
			} else generatingChunk.z++;
			if(xDiff != 0) generatingChunkIndex = (generatingChunkIndex + 1) % 4;
		} else if(xDiff == -zDiff) {
			if(xDiff < 0) generatingChunk.x++;
			else generatingChunk.x--;
			generatingChunkIndex = (generatingChunkIndex + 1) % 4;
		} else generatingChunk += generatingChunkIncrements[generatingChunkIndex];
	}
}

void World::deleteOldChunks() {
	for(auto it = chunks.begin(); it != chunks.end();) {
		if(abs(it->first.x - generatingChunk.x) > RENDER_DISTANCE || 
		   abs(it->first.z - generatingChunk.z) > RENDER_DISTANCE)
			it = chunks.erase(it);
		else it++;
	}
}

void World::generateChunk(const glm::vec3& playerPos) {
	Chunk::Key playerChunk = {getChunkCoord((int)floor(playerPos.x)), getChunkCoord((int)floor(playerPos.z))};

	if(playerChunk != prevPlayerChunk) {
		generatingChunk = playerChunk;
		deleteOldChunks();
		prevPlayerChunk = playerChunk;
		generatingChunkIndex = 0;
		generatingChunks = true;
	} else if(!generatingChunks) return;

	getNextChunkToGen();

	int x = generatingChunk.x, z = generatingChunk.z;
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

	chunks[key]->makeMesh();
}

void World::render() const{
	glBindVertexArray(VAO);
	shader.use();
	blockAtlas.use();
	shader.setInt("tex", blockAtlas.unit);

	for(const auto& kv : chunks) {
		kv.second->render();
	}
}

const BlockType& World::getBlock(int x, int y, int z) const {
	int chunkX = getChunkCoord(x);
	int chunkZ = getChunkCoord(z);

	if(chunks.find({chunkX, chunkZ}) == chunks.end() || y >= CHUNK_HEIGHT || y < 0) return BlockTypes::Air;

	int blockX = getBlockCoord(x, chunkX);
	int blockZ = getBlockCoord(z, chunkZ);

	return chunks.at({chunkX, chunkZ})->getBlock(blockX, y, blockZ);
}

void World::setBlock(int x, int y, int z, const BlockType& block) {
	int chunkX = getChunkCoord(x);
	int chunkZ = getChunkCoord(z);

	if(chunks.find({chunkX, chunkZ}) == chunks.end() || y >= CHUNK_HEIGHT || y < 0) return;


	int blockX = getBlockCoord(x, chunkX);
	int blockZ = getBlockCoord(z, chunkZ);

	chunks.at({chunkX, chunkZ})->setBlock(blockX, y, blockZ, block);
	if(block.isTransparent) {
		if(blockX == 0) chunks.at({chunkX - 1, chunkZ})->makeMesh();
		if(blockX == 15) chunks.at({chunkX + 1, chunkZ})->makeMesh();
		if(blockZ == 0) chunks.at({chunkX, chunkZ - 1})->makeMesh();
		if(blockZ == 15) chunks.at({chunkX, chunkZ + 1})->makeMesh();
	}
}
