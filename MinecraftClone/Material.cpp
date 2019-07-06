#include "stdafx.h"
#include "Material.h"

Material::Material(Shader& shader, TextureSheet& texSheet)  : shader(shader), texSheet(texSheet) {}

void Material::use() {
	shader.use();
	shader.setInt("tex", texSheet.getTexNum());
}
