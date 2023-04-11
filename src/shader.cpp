#include "include/shader.hpp"

#include <cstdio>
#include <string.h>
#include <string>

Shader::Shader() {
    this->shaderId = 0;
    this->uniformModel = 0;
    this->uniformProjection = 0;
}

std::string Shader::readFile(const char* filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream.is_open()) {
        printf("Failed to read %s! File doesn't exist.", filePath);
        return "";
    }

    std::string line = "";
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

void Shader::compileShader(const char* vertexCode, const char* fragmentCode) {
    this->shaderId = glCreateProgram();

    if (!this->shaderId) {
        printf("Error creating this->shaderId program!");
        return;
    }

    addShader(this->shaderId, vertexCode, GL_VERTEX_SHADER);
    addShader(this->shaderId, fragmentCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(this->shaderId);
    glGetProgramiv(this->shaderId, GL_LINK_STATUS, &result);

    if (!result) {
        glGetProgramInfoLog(this->shaderId, sizeof(eLog), NULL, eLog);
        printf("Error linking program: `%s`\n", eLog);
        return;
    }

    glValidateProgram(this->shaderId);
    glGetProgramiv(this->shaderId, GL_VALIDATE_STATUS, &result);

    if (!result) {
        glGetProgramInfoLog(this->shaderId, sizeof(eLog), NULL, eLog);
        printf("Error validating program: `%s`\n", eLog);
        return;
    }

    this->uniformProjection = glGetUniformLocation(this->shaderId, "projection");
    this->uniformModel = glGetUniformLocation(this->shaderId, "model");
    this->uniformView = glGetUniformLocation(this->shaderId, "view");
}

GLuint Shader::getProjectionLocation() {
    return this->uniformProjection;
}

GLuint Shader::getModelLocation() {
    return this->uniformModel;
}

GLuint Shader::getViewLocation() {
    return this->uniformView;
}

void Shader::useShader() {
    glUseProgram(this->shaderId);
}

void Shader::clearShader() {
    if (this->shaderId != 0) {
        glDeleteProgram(this->shaderId);
        this->shaderId = 0;
    }

    this->uniformModel = 0;
    this->uniformProjection = 0;
}

void Shader::addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
    GLuint theShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);

    if (!result) {
        glGetShaderInfoLog(this->shaderId, sizeof(eLog), NULL, eLog);
        printf("Error compiling the %d shader: `%s`\n", shaderType, eLog);
        return;
    }

    glAttachShader(theProgram, theShader);
}


void Shader::createFromString(const char* vertexCode, const char* fragmentCode) {
    compileShader(vertexCode, fragmentCode);
}

void Shader::createFromFiles(const char* vertexPath, const char* fragmentPath) {
    std::string vertexString = readFile(vertexPath);
    std::string fragmentString = readFile(fragmentPath);

    const char* vertexCode = vertexString.c_str();
    const char* fragmentCode = fragmentString.c_str();

    compileShader(vertexCode, fragmentCode);
}
