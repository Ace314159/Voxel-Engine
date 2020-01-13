#version 330 core
in vec3 texCoord;
flat in float lightLevel;

uniform sampler2DArray tex;

out vec4 outColor;

void main() {
	vec3 baseColor = texture(tex, texCoord).xyz;
	outColor = vec4(baseColor * max(0.2, lightLevel / 15.0), 1);
}