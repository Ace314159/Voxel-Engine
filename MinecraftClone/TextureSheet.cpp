#include "stdafx.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>

#include "Object.h"
#include "TextureSheet.h"


TextureSheet::TextureSheet(const std::string& name) {
	std::string fileName = name + ".png";
	glGenTextures(1, &glTexID);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, glTexID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	const GLfloat borderColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	
	//stbi_set_flip_vertically_on_load(true); Texture Coords are flipped vertically
	int numChannels, texWidth, texHeight;
	stbi_uc *data = stbi_load(fileName.c_str(), &texWidth, &texHeight, &numChannels, 4);
	assert(numChannels == 4);
	if(data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		width = texWidth / 8; height = texHeight / 8;
		stbi_image_free(data);
	} else throw std::runtime_error("Unable to load texture " + name);
}

void TextureSheet::setTexCoords(int ID, Vertex* vertices) {
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

int TextureSheet::getTexNum() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, glTexID);
	return 0;
}
