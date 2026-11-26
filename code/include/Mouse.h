#pragma once

#include <GLFW/glfw3.h>
#include "Camera.h"

class Mouse {
public:
    Mouse(Camera* cam, float startX = 640.0f, float startY = 360.0f);

    // Lie la souris à la fenêtre GLFW et enregistre les callbacks
    void attachToWindow(GLFWwindow* window);

private:
    Camera* camera;
    float lastX;
    float lastY;
    bool firstMouse;

    // Méthodes internes appelées par les callbacks
    void onMove(GLFWwindow* window, double xposIn, double yposIn);
    void onScroll(double yoffset);

    // Fonctions statiques exigées par l'API C de GLFW
    static void cursorPosCallback(GLFWwindow* window, double xposIn, double yposIn);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};
