#include "include/light.hpp"
#include "imgui.h"

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity) {
    this->colour = glm::vec3(red, green, blue);
    this->ambientIntensity = aIntensity;
}

void Light::debugLight() {
    ImGui::SeparatorText("Light");
    ImGui::SliderFloat("Red", &this->colour.x, 0.0f, 1.0f);
    ImGui::SliderFloat("Green", &this->colour.y, 0.0f, 1.0f);
    ImGui::SliderFloat("Blue", &this->colour.z, 0.0f, 1.0f);
    ImGui::SliderFloat("Brightness", &this->ambientIntensity, 0.0f, 1.0f);
}

void Light::useLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation) {
    glUniform3f(ambientColourLocation, this->colour.x, this->colour.y, this->colour.z);
    glUniform1f(ambientIntensityLocation, this->ambientIntensity);
}

Light::~Light() {}
