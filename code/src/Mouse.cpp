#include "Mouse.h"

Mouse::Mouse(Camera* cam, float startX, float startY)
    : camera(cam), lastX(startX), lastY(startY), firstMouse(true) {}

void Mouse::attachToWindow(GLFWwindow* window) {
    // Stocke l'adresse de cet objet Mouse dans la fenêtre GLFW
    glfwSetWindowUserPointer(window, this);
    glfwSetCursorPosCallback(window, Mouse::cursorPosCallback);
    glfwSetScrollCallback(window, Mouse::scrollCallback);
}

void Mouse::onMove(GLFWwindow* window, double xposIn, double yposIn) {
    bool isMiddlePressed = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS);
    bool isRightPressed  = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)  == GLFW_PRESS);

    if (!isMiddlePressed && !isRightPressed) {
        firstMouse = true;
        return;
    }

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Inversé car Y va de haut en bas

    lastX = xpos;
    lastY = ypos;

    if (camera) {
        if (isMiddlePressed) {
            camera->processMouseMovement(xoffset, yoffset); // Molette = Rotation
        } else if (isRightPressed) {
            camera->processMousePan(xoffset, yoffset);      // Clic droit = Déplacement
        }
    }
}

void Mouse::onScroll(double yoffset) {
    if (camera) {
        camera->processMouseScroll(static_cast<float>(yoffset));
    }
}

void Mouse::cursorPosCallback(GLFWwindow* window, double xposIn, double yposIn) {
    Mouse* mouse = static_cast<Mouse*>(glfwGetWindowUserPointer(window));
    if (mouse) {
        mouse->onMove(window, xposIn, yposIn);
    }
}

void Mouse::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    Mouse* mouse = static_cast<Mouse*>(glfwGetWindowUserPointer(window));
    if (mouse) {
        mouse->onScroll(yoffset);
    }
}