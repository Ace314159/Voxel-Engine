#pragma once

#include "Shader.h"

class Object {
protected:
	Shader shader;
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 pos;
public:
	Object(const Shader& shader, float x, float y, float z) : shader(shader) {
		updatePos(x, y, z);
	};

	void updatePos(float x, float y, float z) {
		pos = glm::vec3(x, y, z);
		glm::translate(model, pos);
	};

	virtual void render() {
		shader.use();
		shader.setUniformMat("model", model);
	};
};

