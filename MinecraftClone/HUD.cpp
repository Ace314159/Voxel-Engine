#include "stdafx.h"
#include "HUD.h"

HUD::Item::Item(const Shader& shader, const std::string& fileName, unsigned int unitNum,
	float x, float y, float width, float height) :
	x(x), y(y), width(width), height(height), shader(shader), tex(fileName, unitNum, true) {
	vertices[0] = {glm::vec2(x + width / 2, y + height / 2), glm::vec2(1, 1)};
	vertices[1] = {glm::vec2(x - width / 2, y + height / 2), glm::vec2(0, 1)};
	vertices[2] = {glm::vec2(x - width / 2, y - height / 2), glm::vec2(0, 0)};
	vertices[3] = {glm::vec2(x + width / 2, y - height / 2), glm::vec2(1, 0)};

	shader.use();
	shader.setMat("projection", glm::ortho(0.f, (float)SCREEN_WIDTH, 0.f, (float)SCREEN_HEIGHT));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	const GLfloat borderColor[4] = {1, 0, 0, 1};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(HUDVertex),
		(void*)(offsetof(HUDVertex, HUDVertex::pos)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(HUDVertex),
		(void*)(offsetof(HUDVertex, HUDVertex::texCoord)));
	glEnableVertexAttribArray(1);
}

void HUD::Item::render() {
	shader.use();
	shader.setInt("tex", tex.unitNum);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(float), GL_UNSIGNED_INT, 0);
}

HUD::HUD() : shader("hud"), crosshair(shader, "crosshair.png", 1, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 24, 24) {}

void HUD::render() {
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	crosshair.render();
}
