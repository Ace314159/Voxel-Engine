#include "stdafx.h"

#include "Chunk.h"
#include "World.h"

Chunk::Chunk(World* world, const std::vector<Block>& blocks) : world(world), blocks(blocks) {}

void Chunk::makeMesh() {
	mesh.clear();

	for(const Block& block : blocks) {
		if(*block.type == BlockTypes::Air) continue;

		for(int i = 0; i < 6; i++) {
			glm::vec3 adjPos = block.pos + CubeMesh::adjacentFaces[i];
			if(world->getBlock((int)adjPos.x, (int)adjPos.y, (int)adjPos.z).isTransparent)
				mesh.addFace(block.pos, (CubeMesh::Face)i, block.type->texIDs[i]);
		}
	}

	mesh.buffer();
	canRender = true;
}

void Chunk::render() const {
	if(canRender) mesh.render();
}

const BlockType& Chunk::getBlock(unsigned int x, unsigned int y, unsigned int z) const {
	if(x >= CHUNK_LEN || y >= CHUNK_HEIGHT || z >= CHUNK_LEN) return BlockTypes::Air;
	return *blocks[getArrIndex(x, y, z)].type;
}

void Chunk::setBlock(unsigned int x, unsigned y, unsigned z, const BlockType& block) {
	if(x >= CHUNK_LEN || y >= CHUNK_HEIGHT || z >= CHUNK_LEN) return;
	blocks[getArrIndex(x, y, z)].type = &block;

	makeMesh();
}

unsigned int Chunk::getMaxHeight(unsigned int x, unsigned int z) {
	for(int y = CHUNK_HEIGHT - 1; y >= 0; y--) {
		if(*blocks[getArrIndex(x, y, z)].type != BlockTypes::Air) return y;
	}
	return 0;
}
