#include "stdafx.h"
#include "HUD.h"

HUD::Item::Item(const Shader& shader, const std::string& fileName, unsigned int unitNum,
	float x, float y, float width, float height) :
	x(x), y(y), width(width), height(height), shader(shader), tex(fileName) {
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

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void HUD::Item::render() {
	shader.use();
	tex.use();
	shader.setInt("tex", tex.unit);

	glBindVertexBuffer(0, VBO, 0, sizeof(Vertex));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(float), GL_UNSIGNED_INT, 0);
}

GLuint HUD::createVAO() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, offsetof(Item::Vertex, Item::Vertex::pos));
	glVertexAttribFormat(1, 2, GL_FLOAT, GL_FALSE, offsetof(Item::Vertex, Item::Vertex::texCoord));

	glVertexAttribBinding(0, 0);
	glVertexAttribBinding(1, 0);

	return VAO;
}

HUD::HUD() : VAO(createVAO()), shader("hud"),
	crosshair(shader, "crosshair.png", 1, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 24, 24) {}

void HUD::render() {
	glBindVertexArray(VAO);

	glClear(GL_DEPTH_BUFFER_BIT);
	crosshair.render();
}
