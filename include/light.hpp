#pragma once

#include <glad/glad.h>
#include "glm/glm.hpp"

class Light {
public:
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity);

    void debugLight();
    void useLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation);

    ~Light();
private:
    glm::vec3 colour;
    GLfloat ambientIntensity;
};
