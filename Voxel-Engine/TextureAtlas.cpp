#include "stdafx.h"

#include <stb_image.h>
#include "TextureAtlas.h"

TextureAtlas::TextureAtlas(const std::string& fileName) {
	unit = Texture::NEXT_UNIT++;
	glGenTextures(1, &ID);

	int width, height, numChannels;
	stbi_set_flip_vertically_on_load(false);
	GLubyte* data = stbi_load(fileName.c_str(), &width, &height, &numChannels, 4);
	if(!data) throw std::runtime_error("Unable to load texture at " + fileName);


	GLsizei depth = height * width / TEX_SIZE / TEX_SIZE;
	std::vector<GLubyte> parsedData;

	for(size_t tileY = 0; tileY < height / TEX_SIZE; tileY++) {
		for(size_t tileX = 0; tileX < width / TEX_SIZE; tileX++) {
			for(int y = TEX_SIZE - 1; y >= 0; y--) {
				for(int x = 0; x < TEX_SIZE; x++) {
					parsedData.insert(parsedData.end(), {
						data[tileY * width * TEX_SIZE * 4 + y * width * 4 + tileX * TEX_SIZE * 4 + x * 4 + 0],
						data[tileY * width * TEX_SIZE * 4 + y * width * 4 + tileX * TEX_SIZE * 4 + x * 4 + 1],
						data[tileY * width * TEX_SIZE * 4 + y * width * 4 + tileX * TEX_SIZE * 4 + x * 4 + 2],
						data[tileY * width * TEX_SIZE * 4 + y * width * 4 + tileX * TEX_SIZE * 4 + x * 4 + 3],
					});
				}
			}
		}
	}

	use();
	glBindTexture(GL_TEXTURE_2D_ARRAY, ID);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, TEX_SIZE, TEX_SIZE, depth, 0, GL_RGBA, 
				 GL_UNSIGNED_BYTE, parsedData.data());
	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
	stbi_image_free(data);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
