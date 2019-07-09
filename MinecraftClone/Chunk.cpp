#include "stdafx.h"

#include "Chunk.h"
#include "World.h"

Chunk::Chunk(World* world, const std::vector<Block>& blocks) : blocks(blocks) { makeMesh(world); }

void Chunk::makeMesh(World* world) {
	mesh.clear();

	for(const Block& block : blocks) {
		if(block.type == BlockTypes::Air) continue;

		for(int i = 0; i < 6; i++) {
			glm::vec3 adjPos = block.pos + Mesh::adjacentFaces[i];
			if(world->getBlock((int)adjPos.x, (int)adjPos.y, (int)adjPos.z).isTransparent)
				mesh.addFace(block.pos, (Mesh::Face)i, block.type.texIDs[i]);
		}
	}

	mesh.buffer();
}

void Chunk::render() const {
	mesh.render();
}

const BlockType& Chunk::getBlock(unsigned int x, unsigned int y, unsigned int z) const {
	if(x >= CHUNK_X_LEN || y >= CHUNK_Y_LEN || z >= CHUNK_Z_LEN) return BlockTypes::Air;
	return blocks[getArrIndex(x, y, z)].type;
}

unsigned int Chunk::getMaxHeight(unsigned int x, unsigned int z) {
	for(int y = CHUNK_Y_LEN - 1; y >= 0; y--) {
		if(blocks[getArrIndex(x, y, z)].type != BlockTypes::Air) return y;
	}
	return 0;
}
