#pragma once

#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(GLint windowWidth, GLint windowHeight);

    int initialize();

    GLfloat getBufferWidth() { return this->bufferWidth; }
    GLfloat getBufferHeight() { return this->bufferHeight; }

    bool getKey(int code) { return this->keys[code]; }

    GLfloat getXChange();
    GLfloat getYChange();

    bool getMouseGrabbed() { return this->mouseGrabbed; }
    void setMouseGrabbed(bool value);

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
    bool mouseGrabbed;
    bool mouseFirstMoved;

    void createCallback();
    static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
    static void handleMouseCursor(GLFWwindow* window, double xPos, double yPos);
    static void handleMouseButton(GLFWwindow* window, int button, int action, int mods);
};
