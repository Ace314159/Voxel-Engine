#pragma once

#include "Mesh.h"
#include "Shader.h"
#include "TextureAtlas.h"

class Entity {
private:
	Shader shader;
	Mesh mesh;
	const TextureAtlas& entityAtlas;
protected:
	glm::vec3 pos;

	const glm::vec3& boundingBox;
public:
	Entity(const glm::vec3& boundingBox, int textureID, const TextureAtlas& entityAtlas);
	void render() const;
	bool willCollide(const glm::vec3& newPos, const glm::vec3& blockPos) const;
};

