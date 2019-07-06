#pragma once

class Texture {
private:
	static GLuint NEXT_UNIT;
	GLuint ID;

	friend class Material;
public:
	Texture(const std::string& fileName, bool flipVert) : Texture(fileName, Texture::NEXT_UNIT++, flipVert) {};
	Texture(const std::string& fileName, unsigned int unitNum, bool flipVert);

	int width, height;
	unsigned int unitNum;
	void use() { glActiveTexture(GL_TEXTURE0 + unitNum); glBindTexture(GL_TEXTURE_2D, ID); }
};

