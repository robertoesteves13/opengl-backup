#include "include/window.hpp"

#include <iostream>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

void glMsgCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
    std::cout << "GL LOG: type = " << type << ", severity = " << severity << ", message = " << message << "\n";
}

Window::Window(GLint windowWidth, GLint windowHeight) {
    this->width = windowWidth;
    this->height = windowHeight;
    this->mouseFirstMoved = true;
    this->mouseGrabbed = false;

    this->xChange = 0.0f;
    this->yChange = 0.0f;

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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);  

    glfwWindowHint(GLFW_FLOATING, true);  
    glfwWindowHint(GLFW_RESIZABLE, true);  
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, true);  


    this->mainWindow = glfwCreateWindow(this->width, this->height, "OpenGL Course", NULL, NULL);
    if (!this->mainWindow) {
        printf("GLFW mainWindow creation failed!\n");
        glfwTerminate();
        return 1;
    }

    glfwGetFramebufferSize(this->mainWindow, &this->bufferWidth, &this->bufferHeight);
    glfwMakeContextCurrent(this->mainWindow);
    this->createCallback();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("GLAD initialization failed!\n");
        glfwDestroyWindow(this->mainWindow);
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, this->bufferWidth, this->bufferHeight);
    glfwSetWindowUserPointer(this->mainWindow, this);
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(this->mainWindow, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    return 0;
}

void Window::createCallback() {
    glfwSetKeyCallback(this->mainWindow, handleKeys);
    glfwSetCursorPosCallback(this->mainWindow, handleMouseCursor);
    glfwSetMouseButtonCallback(this->mainWindow, handleMouseButton);
}

void Window::updateSize() {
    glfwGetFramebufferSize(this->mainWindow, &this->bufferWidth, &this->bufferHeight);
    glViewport(0, 0, this->bufferWidth, this->bufferHeight);
}

GLfloat Window::getXChange() {
    GLfloat theChange = this->xChange;
    this->xChange = 0.0f;
    return theChange;
}

GLfloat Window::getYChange() {
    GLfloat theChange = this->yChange;
    this->yChange = 0.0f;
    return theChange;
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
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

void Window::setMouseGrabbed(bool value) {
    this->mouseGrabbed = value;

    if (this->mouseGrabbed) {
        this->xChange = 0;
        this->yChange = 0;
        this->mouseFirstMoved = true;
        glfwSetInputMode(this->mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        glfwSetInputMode(this->mainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void Window::beginUi() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Window::drawUi() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Window::handleMouseCursor(GLFWwindow* window, double xPos, double yPos) {
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

void Window::handleMouseButton(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) {
        Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
        theWindow->setMouseGrabbed(true);
    }

}

Window::~Window() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(this->mainWindow);
    glfwTerminate();
}
