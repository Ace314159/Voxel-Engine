#include "stdafx.h"

#include "Renderer.h"

int main() {
	Renderer renderer{};

	renderer.addBlock(0, glm::vec3(0, 0, 0));
	renderer.addBlock(0, glm::vec3(0, 1, 0));

	while(renderer.isRunning()) {
		renderer.render();
	}

	return 0;
}
