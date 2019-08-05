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
	GLuint VBO, EBO;
protected:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
public:
	Mesh();
	~Mesh();

	void buffer();
	void clear();
	void render() const;
};

