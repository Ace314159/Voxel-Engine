#version 330 core
layout (std140) uniform Camera {
	uniform mat4 projection;
	uniform mat4 view;
};

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 iTexCoord;

out vec3 texCoord;

void main() {
	gl_Position = projection * view * vec4(pos, 1.0);
	texCoord = iTexCoord;
}