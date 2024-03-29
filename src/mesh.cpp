#include "include/mesh.hpp"
#include "include/texture.hpp"

#include <imgui.h>

Mesh::Mesh() {
    this->VAO = 0;
    this->VBO = 0;
    this->IBO = 0;
    this->indexCount = 0;
}

void Mesh::createMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices, Texture& texture) {
    this->indexCount = numOfIndices;
    this->meshTexture = texture;

    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    glGenBuffers(1, &this->IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, (void*)(sizeof(vertices[0]) * 3));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Mesh::renderMesh() {
    this->meshTexture.useTexture();

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
    glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Mesh::~Mesh() {
    if (this->IBO != 0) {
        glDeleteBuffers(1, &this->IBO);
        this->IBO = 0;
    }

    if (this->VBO != 0) {
        glDeleteBuffers(1, &this->VBO);
        this->VBO = 0;
    }

    if (this->VAO != 0) {
        glDeleteVertexArrays(1, &this->VAO);
        this->VAO = 0;
    }

    this->indexCount = 0;
}
