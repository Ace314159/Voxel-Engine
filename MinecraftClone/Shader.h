#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class Shader {
public:
	Shader(const std::string& shaderName);
	GLuint ID;

	void use() { glUseProgram(ID); };

	// Uniforms
	GLint getUniformLoc(const std::string& name) const { return glGetUniformLocation(ID, name.c_str()); }
	void setUniformMat(const std::string& name, const glm::mat4& mat) const { 
		glUniformMatrix4fv(getUniformLoc(name), 1, GL_FALSE, glm::value_ptr(mat));
	}
};

