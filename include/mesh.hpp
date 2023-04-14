#pragma once

#include "include/texture.hpp"
#include <glad/glad.h>

class Mesh {
public:
    Mesh();

    void createMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices, Texture& texture);
    void renderMesh();

    ~Mesh();

private:
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;

    Texture meshTexture;
};
