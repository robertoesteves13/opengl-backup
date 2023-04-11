#include "include/window.hpp"
#include "GLFW/glfw3.h"

Window::Window() {
    this->width = 800;
    this->height = 600;
}

Window::Window(GLint windowWidth, GLint windowHeight) {
    this->width = windowWidth;
    this->height = windowHeight;
}

int Window::initialize() {
    if (!glfwInit()) {
        printf("GLFW initialization failed!\n");
        glfwTerminate();
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    this->mainWindow = glfwCreateWindow(this->width, this->height, "OpenGL Course", NULL, NULL);
    if (!this->mainWindow) {
        printf("GLFW mainWindow creation failed!\n");
        glfwTerminate();
        return 1;
    }

    glfwGetFramebufferSize(this->mainWindow, &this->bufferWidth, &this->bufferHeight);
    glfwMakeContextCurrent(this->mainWindow);

    glewExperimental = GL_TRUE;

    int glewError = glewInit();
    if (glewError != GLEW_OK) {
        const unsigned char* msg = glewGetErrorString(glewError);
        printf("GLEW initialization failed: %s\n", msg);
        glfwDestroyWindow(this->mainWindow);
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, this->bufferWidth, this->bufferHeight);

    return 0;
}

Window::~Window() {
    glfwDestroyWindow(this->mainWindow);
    glfwTerminate();
}
