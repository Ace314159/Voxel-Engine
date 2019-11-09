#version 330 core
in vec3 texCoord;
in vec3 normal;
in vec3 fragPos;

uniform sampler2DArray tex;

out vec4 outColor;

vec3 lightColor = vec3(1, 1, 1);

void main() {
	vec3 baseColor = texture(tex, texCoord).xyz;

	float ambientStrength = 0.6;
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(vec3(0, 1, 0));
	float diff = max(dot(norm, lightDir), 0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * baseColor;
	outColor = vec4(result, 1);
}