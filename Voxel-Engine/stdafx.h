#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>

constexpr size_t SCREEN_WIDTH = 1280;
constexpr size_t SCREEN_HEIGHT = 720;

constexpr size_t TEX_SIZE = 16;

constexpr size_t NUM_BLOCKS = 3;

constexpr int CHUNK_LEN = 16;
constexpr int CHUNK_HEIGHT = 128;
constexpr int CHUNK_VOLUME = CHUNK_LEN * CHUNK_LEN * CHUNK_HEIGHT;
