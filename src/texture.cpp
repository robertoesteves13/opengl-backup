#include "include/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture() {
    this->textureId = 0;
    this->width = 0;
    this->height = 0;
    this->bitDepth = 0;
    this->fileLocation = "";
}

Texture::Texture(std::string fileLoc) {
    this->textureId = 0;
    this->width = 0;
    this->height = 0;
    this->bitDepth = 0;
    this->fileLocation = fileLoc;
}

void Texture::loadTexture() {
    unsigned char *texData = stbi_load(this->fileLocation.c_str(), &this->width, &this->height, &this->bitDepth, 0);
    if (!texData) {
        std::cout << "Failed to find: " << this->fileLocation << "\n";
        return;
    }

    glGenTextures(1, &this->textureId);
    glBindTexture(GL_TEXTURE_2D, this->textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(texData);
}

void Texture::useTexture() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->textureId);
}

Texture::~Texture() {
    glDeleteTextures(1, &this->textureId);

    this->textureId = 0;
    this->width = 0;
    this->height = 0;
    this->bitDepth = 0;
    this->fileLocation = "";
}
