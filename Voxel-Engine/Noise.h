#pragma once

#include "PerlinNoise.hpp"

class Noise {
private:
	siv::PerlinNoise perlin;

	double freq;
	int32_t numOctaves;
	double exponent;
public:
	Noise(double freq, int32_t numOctaves, double exponent);
	void setSeed(uint32_t seed);
	double get(double x, double z) const;
};

