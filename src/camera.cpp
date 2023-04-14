#include "include/camera.hpp"
#include "glm/ext/quaternion_geometric.hpp"

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed) {
    this->position = startPosition;
    this->front = glm::vec3(0.0f, 0.0f, 0.0f);
    this->worldUp = startUp;
    this->yaw = startYaw;
    this->pitch = startPitch;

    this->moveSpeed = startMoveSpeed;
    this->turnSpeed = startTurnSpeed;

    update();
}

void Camera::update() {
    this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->front.y = sin(glm::radians(this->pitch));
    this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->front = glm::normalize(this->front);

    this->right = glm::normalize(glm::cross(this->front, this->worldUp));
    this->up = glm::normalize(glm::cross(this->right, this->front));
}

glm::mat4 Camera::calculateViewMatrix() {
    return glm::lookAt(this->position, this->position + this->front, this->up);
}

void Camera::keyControl(Window* window, GLfloat deltaTime) {
    GLfloat velocity = this->moveSpeed * deltaTime;

    if (window->getKey(GLFW_KEY_ESCAPE)) {
        window->setMouseGrabbed(false);
    }

    if (window->getKey(GLFW_KEY_W)) {
        this->position += this->front * this->moveSpeed * velocity;
    }
    if (window->getKey(GLFW_KEY_S)) {
        this->position -= this->front * this->moveSpeed * velocity;
    }
    if (window->getKey(GLFW_KEY_A)) {
        this->position -= this->right * this->moveSpeed * velocity;
    }
    if (window->getKey(GLFW_KEY_D)) {
        this->position += this->right * this->moveSpeed * velocity;
    }
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange) {
    xChange *= turnSpeed;
    yChange *= turnSpeed;

    this->yaw += xChange;
    this->pitch += yChange;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    update();
}


Camera::~Camera() {}
