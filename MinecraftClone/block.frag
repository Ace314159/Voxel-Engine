#version 330 core
in vec3 texCoord;

uniform sampler2DArray tex;

out vec4 outColor;

void main() {
	outColor = texture(tex, texCoord);
}