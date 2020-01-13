#include "stdafx.h"

#include "Chunk.h"
#include "World.h"

Chunk::Chunk(World* world, const std::vector<Block>& blocks, Chunk::Key key) : world(world), blocks(blocks),
	lightMap(CHUNK_VOLUME), key(key) {
	makeLightMap();
}

void Chunk::makeLightMap() {
	std::fill(lightMap.begin(), lightMap.end(), 0.0f);

	std::queue<size_t> blocksToCheck;
	for(int x = 0; x < CHUNK_LEN; x++) {
		for(int z = 0; z < CHUNK_LEN; z++) {
			size_t index = getArrIndex(x, CHUNK_HEIGHT - 1, z);
			blocksToCheck.push(index);
			lightMap[index] = 15;
		}
	}

	while(!blocksToCheck.empty()) {
		size_t& curIndex = blocksToCheck.front();
		float curLightLevel = lightMap[curIndex];

		glm::ivec3 indexPos;
		indexPos.y = curIndex % CHUNK_HEIGHT;
		curIndex /= CHUNK_HEIGHT;
		indexPos.x = curIndex % CHUNK_LEN;
		curIndex /= CHUNK_LEN;
		indexPos.z = curIndex % CHUNK_LEN;
		glm::ivec3 curPos = {
			world->getWorldCoord(key.x, indexPos.x),
			indexPos.y,
			world->getWorldCoord(key.z, indexPos.z)
		};

		blocksToCheck.pop();

		for(int i = 0; i < 6; i++) {
			glm::ivec3 adjPos = curPos + CubeMesh::adjacentFaces[i];
			unsigned int x = (unsigned int)adjPos.x;
			unsigned int y = (unsigned int)adjPos.y;
			unsigned int z = (unsigned int)adjPos.z;
			if(y < 0) continue;
			
			const BlockType& adjBlock = getBlock(x, y, z);
			if(adjBlock.isTransparent) {
				bool propogated = false;
				unsigned int maxHeight = getMaxHeight(indexPos.x, indexPos.z);
				if(CubeMesh::adjacentFaces[i].y == 0 || y < maxHeight) {
					if(world->getLightLevel(x, y, z) < curLightLevel - 1) {
						propogated = true;
						world->setLightLevel(x, y, z, curLightLevel - 1);
					}
				} else {
					if(world->getLightLevel(x, y, z) < curLightLevel) {
						propogated = true;
						world->setLightLevel(x, y, z, curLightLevel);
					}
				}
				
				if(propogated) {
					int adjChunkX = world->getChunkCoord(x), adjChunkZ = world->getChunkCoord(z);
					if(adjChunkX == key.x && adjChunkZ == key.z)
						blocksToCheck.push(getArrIndex(
							world->getBlockCoord(x, key.x),
							y,
							world->getBlockCoord(z, key.z))
						);
				}
			}
		}
	}
}

void Chunk::makeMesh() {
	makeLightMap();

	mesh.clear();

	for(const Block& block : blocks) {
		if(*block.type == BlockTypes::Air) continue;

		for(int i = 0; i < 6; i++) {
			glm::ivec3 adjPos = block.pos + CubeMesh::adjacentFaces[i];
			int x = adjPos.x;
			int y = adjPos.y;
			int z = adjPos.z;
			if (world->getBlock(x, y, z).isTransparent)
				mesh.addFace(block.pos, (CubeMesh::Face)i, block.type->texIDs[i], world->getLightLevel(x, y, z));
		}
	}

	mesh.buffer();
	_canRender = true;
}

void Chunk::render() const {
	if(_canRender) mesh.render();
}

const BlockType& Chunk::getBlock(unsigned int x, unsigned int y, unsigned int z) const {
	if(x >= CHUNK_LEN || y >= CHUNK_HEIGHT || z >= CHUNK_LEN) return BlockTypes::Air;
	return *blocks[getArrIndex(x, y, z)].type;
}

void Chunk::setBlock(unsigned int x, unsigned int y, unsigned int z, const BlockType& block) {
	if(x >= CHUNK_LEN || y >= CHUNK_HEIGHT || z >= CHUNK_LEN) return;
	blocks[getArrIndex(x, y, z)].type = &block;

	makeMesh();
}

float Chunk::getLightLevel(unsigned int x, unsigned int y, unsigned z) {
	if (x >= CHUNK_LEN || y >= CHUNK_HEIGHT || z >= CHUNK_LEN) return 0xFF;
	return lightMap[getArrIndex(x, y, z)];
}

void Chunk::setLightLevel(unsigned int x, unsigned int y, unsigned z, float lightLevel) {
	if(x >= CHUNK_LEN || y >= CHUNK_HEIGHT || z >= CHUNK_LEN) return;
	lightMap[getArrIndex(x, y, z)] = lightLevel;
}

unsigned int Chunk::getMaxHeight(unsigned int x, unsigned int z) {
	for(int y = CHUNK_HEIGHT - 1; y >= 0; y--) {
		if(*blocks[getArrIndex(x, y, z)].type != BlockTypes::Air) return y;
	}
	return 0;
}
