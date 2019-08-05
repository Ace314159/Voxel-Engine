#include "stdafx.h"

#include "Entity.h"


Entity::Entity(const glm::vec3& boundingBox, int textureID, const TextureAtlas& entityAtlas) : 
	boundingBox(boundingBox), shader("entity", "block"), entityAtlas(entityAtlas) {
	float xLen = boundingBox.x;
	float yLen = boundingBox.y;
	float zLen = boundingBox.z;
	mesh.vertices = {
		// Front 
		{ {xLen, yLen, zLen}, {1, 1, textureID + 0} },
		{ {0,    yLen, zLen}, {0, 1, textureID + 0} },
		{ {0,       0, zLen}, {0, 0, textureID + 0} },
		{ {xLen,    0, zLen}, {1, 0, textureID + 0} },
		// Right 
		{ {xLen, yLen,    0}, {1, 1, textureID + 1} },
		{ {xLen, yLen, zLen}, {0, 1, textureID + 1} },
		{ {xLen,    0, zLen}, {0, 0, textureID + 1} },
		{ {xLen,    0,    0}, {1, 0, textureID + 1} },
		// Back 
		{ {0,    yLen,    0}, {1, 1, textureID + 2} },
		{ {xLen, yLen,    0}, {0, 1, textureID + 2} },
		{ {xLen,    0,    0}, {0, 0, textureID + 2} },
		{ {0,       0,    0}, {1, 0, textureID + 2} },
		// Left 
		{ {0,    yLen, zLen}, {1, 1, textureID + 3} },
		{ {0,    yLen,    0}, {0, 1, textureID + 3} },
		{ {0,       0,    0}, {0, 0, textureID + 3} },
		{ {0,       0,    1}, {1, 0, textureID + 3} },
		// Top 
		{ {xLen, yLen,    0}, {1, 1, textureID + 4} },
		{ {0,    yLen,    0}, {0, 1, textureID + 4} },
		{ {0,    yLen, zLen}, {0, 0, textureID + 4} },
		{ {xLen, yLen, zLen}, {1, 0, textureID + 4} },
		// Bottom 
		{ {xLen,    0, zLen}, {1, 1, textureID + 5} },
		{ {0,       0, zLen}, {0, 1, textureID + 5} },
		{ {0,       0,    0}, {0, 0, textureID + 5} },
		{ {xLen,    0,    0}, {1, 0, textureID + 5} },
	};
	for(unsigned int i = 0; i < 24; i += 4) {
		mesh.indices.insert(mesh.indices.end(), {
			0 + i, 1 + i, 2 + i,
			2 + i, 3 + i, 0 + i,
		});
	}
	mesh.buffer();
}

void Entity::render() const {
	shader.use();
	shader.setMat("model", glm::translate(glm::mat4(1), pos));

	entityAtlas.use();
	shader.setInt("tex", entityAtlas.unit);

	mesh.render();
}

bool Entity::willCollide(const glm::vec3& newPos, const glm::vec3& blockPos) const {
	return 
		blockPos.x <= newPos.x + boundingBox.x && blockPos.x + 1 >= pos.x &&
		blockPos.y <= newPos.y + boundingBox.y && blockPos.y + 1 >= pos.y &&
		blockPos.z <= newPos.z + boundingBox.z && blockPos.z + 1 >= pos.z;
}
