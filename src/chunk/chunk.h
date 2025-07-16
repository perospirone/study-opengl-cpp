#pragma once

#include <vector>

class Chunk {
  public:
    static const int WIDTH = 16;
    static const int HEIGHT = 16;
    static const int DEPTH = 16;

    static unsigned char blocks[WIDTH][HEIGHT][DEPTH];  // Fixed declaration

    unsigned int vao, vbo;
    std::vector<float> mesh_vertices;

    Chunk();

    void GenerateMesh();
    void Draw();

};
