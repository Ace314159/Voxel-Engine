#include "stdafx.h"

#include "Renderer.h"

int main() {
	Renderer renderer{};

	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			renderer.addBlock(0, glm::vec3(i, 0, j));
		}
	}

	while(renderer.isRunning()) {
		renderer.render();
	}

	return 0;
}
