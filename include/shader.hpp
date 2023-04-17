#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <glad/glad.h>

class Shader {
public:
    Shader();

    void createFromString(const char* vertexCode, const char* fragmentCode);
    void createFromFiles(const char* vertexPath, const char* fragmentPath);

    std::string readFile(const char* filePath);

    GLuint getProjectionLocation();
    GLuint getModelLocation();
    GLuint getViewLocation();
    GLuint getAmbientIntensityLocation();
    GLuint getAmbientColourLocation();

    void useShader();
    void clearShader();

    ~Shader();

private:
    GLuint shaderId, uniformProjection, uniformModel, uniformView, uniformAmbientIntensity, uniformAmbientColour;

    void compileShader(const char* vertexCode, const char* fragmentCode);
    void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};
