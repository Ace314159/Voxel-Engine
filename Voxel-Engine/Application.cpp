#include "stdafx.h"

#include "Renderer.h"

int main() {
	try {
		Renderer renderer;

		while(renderer.isRunning()) {
			renderer.render();
		}
	}
	catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
		throw e;
		return -1;
	}

	return 0;
}
