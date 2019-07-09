#pragma once

#include "Texture.h"

class TextureAtlas : public Texture {
public:
	TextureAtlas(const std::string& fileName);

	void use() override { glActiveTexture(GL_TEXTURE0 + unit); };
};

