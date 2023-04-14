#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class Texture {
public:
    Texture();
    Texture(std::string fileLoc);

    void loadTexture();
    void useTexture();

    ~Texture();
private:
    GLuint textureId;
    int width, height, bitDepth;

    std::string fileLocation;
};
