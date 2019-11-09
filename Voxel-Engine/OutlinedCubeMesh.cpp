#include "stdafx.h"

#include "OutlinedCubeMesh.h"

OutlinedCubeMesh::OutlinedCubeMesh() : shader("block", "outlinedBlock") {}

void OutlinedCubeMesh::render() {
	shader.use();

	glDisable(GL_DEPTH_TEST);
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	CubeMesh::render();

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
