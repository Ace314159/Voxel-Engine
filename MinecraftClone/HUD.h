#pragma once

#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"

class HUD {
private:
	Shader shader;

	class Item {
	private:
		GLuint VAO, VBO, EBO;

		float x, y; // Center
		float width, height;

		HUDVertex vertices[4];

		GLuint indices[6] = {
			0, 1, 2,
			2, 3, 0,
		};
	public:
		Texture tex;
		const Shader& shader;

		Item(const Shader& shader, const std::string& fileName, unsigned int unitNum,
			 float x, float y, float width, float height);
		void render();
	};

	// Items
	Item crosshair;
public:
	HUD();

	void render();
};

