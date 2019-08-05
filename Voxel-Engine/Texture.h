#pragma once

#include <glad/glad.h>

class Texture {
protected:
	static GLuint NEXT_UNIT;
	GLuint ID;
public:
	Texture() {};
	Texture(const std::string& fileName);

	unsigned int unit;
	virtual void use() const { glActiveTexture(GL_TEXTURE0 + unit); }
};

