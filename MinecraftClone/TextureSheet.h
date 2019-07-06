#pragma once

#include "Texture.h"
#include "Vertex.h"

class TextureSheet {
private:
	Texture tex;
	int width, height;

	friend class Material;
public:
	TextureSheet(const std::string& name);
	void setTexCoords(int ID, ObjectVertex* vertices);
};

