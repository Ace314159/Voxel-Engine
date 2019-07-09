#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>

class Mesh {
public:
	struct Vertex {
		glm::vec3 pos;
		glm::vec3 texCoord;
	};
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	GLuint VBO, EBO;

	static glm::vec3 faces[6][4];
	static glm::vec2 texCoords[4];
public:
	Mesh();
	~Mesh();

	enum class Face { FRONT = 0, RIGHT = 1, BACK = 2, LEFT = 3, TOP = 4, BOTTOM = 5 };
	static glm::vec3 adjacentFaces[6];

	void addFace(const glm::vec3& pos, Face type, int textureID);
	void buffer();
	void clear();
	void render() const;
};

