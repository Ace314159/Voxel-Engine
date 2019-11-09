#include "stdafx.h"

#include "Noise.h"

Noise::Noise(double freq, int32_t numOctaves, double exponent) : freq(freq), numOctaves(numOctaves),
	exponent(exponent) {}

void Noise::setSeed(uint32_t seed) {
	perlin.reseed(seed);
}

double Noise::get(double x, double z) const {
	return pow(perlin.octaveNoise0_1(x / freq, z / freq, numOctaves), exponent);
}
