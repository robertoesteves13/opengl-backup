#pragma once

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window();
    Window(GLint windowWidth, GLint windowHeight);

    int initialize();

    GLfloat getBufferWidth() { return this->bufferWidth; }
    GLfloat getBufferHeight() { return this->bufferHeight; }

    bool getKey(int code) { return this->keys[code]; }

    GLfloat getXChange();
    GLfloat getYChange();

    bool getShouldClose() { return glfwWindowShouldClose(this->mainWindow); }

    void swapBuffers() { glfwSwapBuffers(this->mainWindow); }

    ~Window(); 

private:
    GLFWwindow *mainWindow;

    GLint width, height;
    GLint bufferWidth, bufferHeight;

    bool keys[1024];

    GLfloat lastX;
    GLfloat lastY;
    GLfloat xChange;
    GLfloat yChange;
    bool mouseFirstMoved;

    void createCallback();
    static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
    static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};
