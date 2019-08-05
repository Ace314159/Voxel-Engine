#include "stdafx.h"

#include "Renderer.h"

int main() {
	Renderer renderer;

	while(renderer.isRunning()) {
		renderer.render();
	}

	return 0;
}
