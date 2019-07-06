#pragma once

#include "Shader.h"
#include "TextureSheet.h"

class Material {
public:
	Material(Shader& shader, TextureSheet& texSheet);

	Shader& shader;
	TextureSheet& texSheet;

	void use();
};

