#include "stdafx.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Object.h"
#include "TextureSheet.h"


TextureSheet::TextureSheet(const std::string& name) : tex(name + ".png", 0, false),
width(tex.width / 8), height(tex.height / 8) {
	tex.use();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	const GLfloat borderColor[4] = {1, 0, 0, 1};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
}

void TextureSheet::setTexCoords(int ID, ObjectVertex* vertices) {
	int row = ID / width;
	int col = ID - row * width;
	float left = (float)col / width;
	float right = (float)(col + 1) / width;
	float top = (float)row / height; // Flipped Vertically
	float bottom = (float)(row + 1) / height; // Flipped Vertically

	vertices[0].texCoord = glm::vec2(right, top); // Top Right
	vertices[1].texCoord = glm::vec2(left, top); // Top Left
	vertices[2].texCoord = glm::vec2(left, bottom); // Bottom Left
	vertices[3].texCoord = glm::vec2(right, bottom); // Bottom Right
}
