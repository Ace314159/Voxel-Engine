#version 330 core
in vec2 texCoord;

uniform sampler2D tex;

out vec4 outColor;

void main() {
	vec4 texColor = texture(tex, texCoord);
	outColor = texColor;
	if(texColor.a < 0.1) outColor = vec4(1, 0, 0, 1);
}