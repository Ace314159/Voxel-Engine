#include "stdafx.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "Texture.h"

unsigned int Texture::NEXT_UNIT = 0;

Texture::Texture(const std::string& fileName, unsigned int unitNum, bool flipVert) : unitNum(unitNum) {
	if(unitNum > Texture::NEXT_UNIT) Texture::NEXT_UNIT = unitNum;
	glGenTextures(1, &ID);

	int numChannels;
	if(flipVert) stbi_set_flip_vertically_on_load(true);
	else stbi_set_flip_vertically_on_load(false);
	stbi_uc* data = stbi_load(fileName.c_str(), &width, &height, &numChannels, 4);
	if(data) {
		assert(numChannels == 4);
		use();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	} else throw std::runtime_error("Unable to load texture at " + fileName);
}
