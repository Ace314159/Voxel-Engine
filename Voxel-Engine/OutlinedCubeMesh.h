#pragma once

#include "CubeMesh.h"
#include "Shader.h"


class OutlinedCubeMesh : public CubeMesh {
private:
	Shader shader;
public:
	OutlinedCubeMesh();
	void render();
};

