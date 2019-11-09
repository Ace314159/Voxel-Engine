#pragma once

class Biome {
public:
	const BlockType& mainBlock;
	Biome(const BlockType& mainBlock) : mainBlock(mainBlock) {};
	const int STONE_Y = 20;
public:
	virtual void generateColumn(std::vector<Block>& blocks, double e, int worldX, int worldZ) {
		int elevation = (int)round(e * CHUNK_HEIGHT);
		if(elevation > STONE_Y) {
			for(int y = 0; y <= STONE_Y; y++) {
				blocks.emplace_back(BlockTypes::Stone, glm::vec3(worldX, y, worldZ));
			}
			for(int y = STONE_Y + 1; y <= elevation; y++) {
				blocks.emplace_back(mainBlock, glm::vec3(worldX, y, worldZ));
			}
		} else {
			for(int y = 0; y <= elevation; y++) {
				blocks.emplace_back(BlockTypes::Stone, glm::vec3(worldX, y, worldZ));
			}
		}
		for(int y = elevation + 1; y < CHUNK_HEIGHT; y++) {
			blocks.emplace_back(BlockTypes::Air, glm::vec3(worldX, y, worldZ));
		}
	};
};

namespace Biomes {
	class Grassland : public Biome {
	public:
		Grassland() : Biome(BlockTypes::Grass) {};
		virtual void generateColumn(std::vector<Block>& blocks, double e, int worldX, int worldZ) {
			int elevation = (int)round(e * CHUNK_HEIGHT);
			if(elevation > STONE_Y) {
				for(int y = 0; y <= STONE_Y; y++) {
					blocks.emplace_back(BlockTypes::Stone, glm::vec3(worldX, y, worldZ));
				}
				for(int y = STONE_Y + 1; y < elevation; y++) {
					blocks.emplace_back(BlockTypes::Dirt, glm::vec3(worldX, y, worldZ));
				}
				blocks.emplace_back(mainBlock, glm::vec3(worldX, elevation, worldZ));
			} else {
				for(int y = 0; y <= elevation; y++) {
					blocks.emplace_back(BlockTypes::Stone, glm::vec3(worldX, y, worldZ));
				}
			}
			for(int y = elevation + 1; y < CHUNK_HEIGHT; y++) {
				blocks.emplace_back(BlockTypes::Air, glm::vec3(worldX, y, worldZ));
			}
		};
	};

	class Desert : public Biome {
	public:
		Desert() : Biome(BlockTypes::Sand) {};
	};

	class Ocean : public Biome {
	public:
		Ocean() : Biome(BlockTypes::Water) {};
	};

	class Tundra : public Biome {
	public:
		Tundra() : Biome(BlockTypes::Snow) {};
	};

	std::unique_ptr<Biome> getBiome(double e, double m) {
		if(e < 0.1) return std::make_unique<Ocean>();
		if(e < 0.12) return std::make_unique<Desert>();

		if(e > 0.75) {
			if(m < 0.25) return std::make_unique<Tundra>();
			else return std::make_unique<Grassland>();
		}

		if(e > 0.5 || m > 0.25) return std::make_unique<Grassland>();
		else return std::make_unique<Desert>();
	}
}
