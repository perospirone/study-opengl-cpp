#include "chunk.h"

const int Chunk::WIDTH;
const int Chunk::HEIGHT;
const int Chunk::DEPTH;

unsigned char Chunk::blocks[Chunk::WIDTH][Chunk::HEIGHT][Chunk::DEPTH];  // Correct definition

Chunk::Chunk() {
      // Initialize all blocks to 0
      for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
          for (int z = 0; z < DEPTH; ++z) {
            blocks[x][y][z] = 0;
          }
        }
      }

      for (int x = 0; x <= 8; ++x) {
        for (int y = 0; y <= 8; ++y) {
          for (int z = 0; z <= 8; ++z) {
            blocks[x][y][z] = 1;
          }
        }
      }
    }

