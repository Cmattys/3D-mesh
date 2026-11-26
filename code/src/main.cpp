#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "FileReader.h"
#include "Fill_Vector.h"
#include "Mesh.h"
#include "Shader.h"
#include "Mesh_Renderer.h"
#include "Camera.h"
#include "Mouse.h"

int main() {
    // --- Chargement du fichier obj dans nos classes ---
    FileReader lecteur("../Fichier_obj/jointure_v2.obj");
    Fill_Vector Tab(lecteur);
    Tab.export_data();
    const std::vector<std::array<float,3>>& points = Tab.getPoints();
    const std::vector<std::array<int,3>>& faces = Tab.getFaces();
    Mesh Me(points, faces);

    // -- Permet d'ouvrir la fenetre OpenGL --
    if (!glfwInit()) {
        std::cerr << "Erreur d'initialisation de GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Viewer - 3D Mesh", nullptr, nullptr);
    if (!window) {
        std::cerr << "Erreur création fenêtre GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Erreur initialisation GLEW" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // -- Mets le shader et remplit les matrices pour l'affichage --
    Shader monShader("../vertex.glsl", "../fragment.glsl");
    Mesh_Renderer renderer(&monShader);
    
    renderer.set_buffer();
    renderer.updateFromMesh(&Me);
    renderer.setRenderMode(RenderMode::WIREFRAME);

    // Initialisation de la caméra et liaison de la souris
    Camera camera;
    camera.focusOnMesh(points); // Cadrage, vitesses et farPlane réglés automatiquement !

    Mouse mouse(&camera);
    mouse.attachToWindow(window);

    // Variables pour calculer le deltaTime
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // Boucle du programme 
    while (!glfwWindowShouldClose(window)) {
        // 1. Calcul du deltaTime
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // 2. Raccourcis clavier pour les modes d'affichage
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
            renderer.setRenderMode(RenderMode::FILL);      // Plein
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
            renderer.setRenderMode(RenderMode::WIREFRAME); // Arêtes
        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
            renderer.setRenderMode(RenderMode::POINTS);    // Sommets

        // 3. Déplacements de la caméra au clavier (ZQSD/WASD + Espace/Shift)
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.processKeyboard(Direction::FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.processKeyboard(Direction::BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.processKeyboard(Direction::LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.processKeyboard(Direction::RIGHT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            camera.processKeyboard(Direction::UP, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            camera.processKeyboard(Direction::DOWN, deltaTime);

        // 4. Effacer l'écran
        glClearColor(0.15f, 0.15f, 0.18f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 5. Dessiner l'objet en passant l'adresse de la caméra
        renderer.draw(&camera);

        // 6. Échanger les buffers et récupérer les événements
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}