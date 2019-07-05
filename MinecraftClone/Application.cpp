#include "stdafx.h"

#include "Renderer.h"

int main() {
	Renderer renderer{};

	renderer.addCube(0, 0, 0);

	while(renderer.isRunning()) {
		renderer.render();
	}

	return 0;
}
