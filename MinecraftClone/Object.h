#pragma once

#include "Material.h"

class Object {
private:
	glm::vec3 pos;
protected:
	Material& material;
	glm::mat4 model = glm::mat4(1.0f);
public:
	Object(Material& material, const glm::vec3& pos) : material(material) {
		updatePos(pos);
	};

	void updatePos(const glm::vec3& newPos) {
		pos = newPos;
		model = glm::translate(glm::mat4(1.0f), pos);
	};

	virtual void render() {
		material.use();
		material.shader.setMat("model", model);
	};
};

