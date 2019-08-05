#version 330 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 iTexCoord;

uniform mat4 projection;

out vec2 texCoord;

void main() {
	gl_Position = projection * vec4(pos, 0, 1);
	texCoord = iTexCoord;
}