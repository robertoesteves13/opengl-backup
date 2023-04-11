#include "include/window.hpp"
#include "GLFW/glfw3.h"

Window::Window() {
    this->width = 800;
    this->height = 600;

    for (size_t i = 0; i < 1024; ++i) {
        this->keys[i] = false;
    }
}

Window::Window(GLint windowWidth, GLint windowHeight) {
    this->width = windowWidth;
    this->height = windowHeight;

    for (size_t i = 0; i < 1024; ++i) {
        this->keys[i] = false;
    }
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
    this->createCallback();
    glfwSetInputMode(this->mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
    glfwSetWindowUserPointer(this->mainWindow, this);

    return 0;
}

void Window::createCallback() {
    glfwSetKeyCallback(this->mainWindow, handleKeys);
    glfwSetCursorPosCallback(this->mainWindow, handleMouse);
}

GLfloat Window::getXChange() {
    GLfloat theChange = this->xChange;
    this->xChange = 0;
    return theChange;
}

GLfloat Window::getYChange() {
    GLfloat theChange = this->yChange;
    this->yChange = 0;
    return theChange;
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            theWindow->keys[key] = true;
        }
        else if (action == GLFW_RELEASE) {
            theWindow->keys[key] = false;
        }
    }

}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos) {
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (theWindow->mouseFirstMoved) {
        theWindow->lastX = xPos;
        theWindow->lastY = yPos;
        theWindow->mouseFirstMoved = false;
    }

    theWindow->xChange = xPos - theWindow->lastX;
    theWindow->yChange = theWindow->lastY - yPos;

    theWindow->lastX = xPos;
    theWindow->lastY = yPos;
}

Window::~Window() {
    glfwDestroyWindow(this->mainWindow);
    glfwTerminate();
}
