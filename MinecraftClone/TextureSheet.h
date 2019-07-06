#pragma once

#include "Vertex.h"

class TextureSheet {
private:
	GLuint glTexID;
	int width, height;
public:
	TextureSheet(const std::string& name);
	void setTexCoords(int ID, Vertex* vertices);
	int getTexNum();
};

