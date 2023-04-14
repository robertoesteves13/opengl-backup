#include <cmath>
#include <cstring>
#include <memory>
#include <vector>
#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "include/mesh.hpp"
#include "include/shader.hpp"
#include "include/window.hpp"
#include "include/camera.hpp"
#include "include/texture.hpp"

int main() {
    std::vector<std::unique_ptr<Mesh>> meshList;
    std::vector<std::unique_ptr<Shader>> shaderList;

    float curAngle = 0.0f;

    GLfloat deltaTime = 0.0f;
    GLfloat lastTime = 0.0f;

    // You should copy this folder on the same path as the executable
    static const char* vShader = "shaders/vert.glsl";
    static const char* fShader = "shaders/frag.glsl";

    Window mainWindow = Window(800, 600);
    if (mainWindow.initialize() != 0) {
        return 1;
    }

    // Create Objects
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 1.0f, 0.5f, 0.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.5f, 1.0f
    };

    std::unique_ptr<Texture> meshTexture = std::make_unique<Texture>(Texture("resources/brick-02.png"));
    meshTexture->loadTexture();

    std::unique_ptr<Mesh> obj1 = std::make_unique<Mesh>(Mesh());
    obj1->createMesh(vertices, indices, 20, 12, *meshTexture);
    meshList.push_back(std::move(obj1));

    // Create Shaders
    std::unique_ptr<Shader> shader1 = std::make_unique<Shader>(Shader());
    shader1->createFromFiles(vShader, fShader);
    shaderList.push_back(std::move(shader1));

    std::unique_ptr<Camera> camera = std::make_unique<Camera>(Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 1.25f, 0.25f));

    GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
    glm::mat4 projection = glm::perspective(45.0f, (GLfloat) mainWindow.getBufferWidth() / (GLfloat) mainWindow.getBufferHeight(), 0.1f, 100.0f);

    while(!mainWindow.getShouldClose()) {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        glfwPollEvents();

        camera->keyControl(&mainWindow, deltaTime);
        if (mainWindow.getMouseGrabbed()) {
            camera->mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderList[0]->useShader();
        uniformModel = shaderList[0]->getModelLocation();
        uniformProjection = shaderList[0]->getProjectionLocation();
        uniformView = shaderList[0]->getViewLocation();

        curAngle += 0.1f;
        if (curAngle >= 360) {
            curAngle -= 360;
        }

        glm::mat4 model(1.0f);

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera->calculateViewMatrix()));

        meshList[0]->renderMesh();

        glUseProgram(0);

        mainWindow.swapBuffers();
    }

    meshList.clear();
    shaderList.clear();
    return 0;
}
