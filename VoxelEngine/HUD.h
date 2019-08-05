#pragma once

#include "Shader.h"
#include "Texture.h"

class HUD {
private:
	Shader shader;
	GLuint VAO;

	class Item {
	private:
		GLuint VBO, EBO;

		float x, y; // Center
		float width, height;

		struct Vertex {
			glm::vec2 pos;
			glm::vec2 texCoord;
		};

		Vertex vertices[4];

		GLuint indices[6] = {
			0, 1, 2,
			2, 3, 0,
		};

		friend class HUD;
	public:
		Texture tex;
		const Shader& shader;

		Item(const Shader& shader, const std::string& fileName, unsigned int unitNum,
			 float x, float y, float width, float height);
		void render();
	};

	// Items
	Item crosshair;

	GLuint createVAO();
public:
	HUD();

	void render();
};

