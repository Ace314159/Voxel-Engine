#version 330 core
in vec2 texCoord;

uniform sampler2D tex;

out vec4 outColor;

void main() {
	vec4 texColor = texture(tex, texCoord);
	if(texColor.a < 0.1) discard;
	outColor = texColor;
}