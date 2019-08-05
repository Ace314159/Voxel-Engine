#include "stdafx.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Texture.h"

unsigned int Texture::NEXT_UNIT = 0;

Texture::Texture(const std::string& fileName) {
	unit = Texture::NEXT_UNIT++;
	glGenTextures(1, &ID);

	int width, height, numChannels;
	stbi_set_flip_vertically_on_load(true);
	stbi_uc* data = stbi_load(fileName.c_str(), &width, &height, &numChannels, 4);
	if(!data) throw std::runtime_error("Unable to load texture at " + fileName);

	use();
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}
