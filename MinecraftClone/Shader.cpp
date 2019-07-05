#include "stdafx.h"
#include "Shader.h"

Shader::Shader(const std::string& shaderName) {
	std::ifstream vShaderFile(shaderName + ".vert"), fShaderFile(shaderName + ".frag");

	std::stringstream vBuffer;
	vBuffer << vShaderFile.rdbuf();
	std::string vShaderCode = vBuffer.str().c_str();
	std::stringstream fBuffer;
	fBuffer << fShaderFile.rdbuf();
	std::string fShaderCode = fBuffer.str();

	const char* vShaderCodeC = vShaderCode.c_str();
	const char* fShaderCodeC = fShaderCode.c_str();

	GLuint vShader, fShader;
	int success;
	char infoLog[512];

	vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vShaderCodeC, nullptr);
	glCompileShader(vShader);
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(vShader, 512, nullptr, infoLog);
		throw std::runtime_error("Vertex Shader " + shaderName + " failed to compile:\n" + infoLog);
	};

	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fShaderCodeC, nullptr);
	glCompileShader(fShader);
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(fShader, 512, nullptr, infoLog);
		throw std::runtime_error("Fragment Shader " + shaderName + " failed to compile:\n" + infoLog);
	};

	ID = glCreateProgram();
	glAttachShader(ID, vShader);
	glAttachShader(ID, fShader);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(ID, 512, nullptr, infoLog);
		throw std::runtime_error("Shader " + shaderName + " failed to link:\n" + 
			infoLog);
	}

	glDeleteShader(vShader);
	glDeleteShader(fShader);
}
