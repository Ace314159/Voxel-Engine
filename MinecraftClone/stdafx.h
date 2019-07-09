#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

constexpr size_t SCREEN_WIDTH = 1280;
constexpr size_t SCREEN_HEIGHT = 720;

constexpr size_t TEX_SIZE = 8;

constexpr size_t NUM_BLOCKS = 3;

constexpr size_t CHUNK_X_LEN = 16;
constexpr size_t CHUNK_Y_LEN = 16;
constexpr size_t CHUNK_Z_LEN = 16;
constexpr size_t CHUNK_VOLUME = CHUNK_X_LEN * CHUNK_Y_LEN * CHUNK_Z_LEN;
