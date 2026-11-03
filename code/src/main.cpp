#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "FileReader.h"
#include "Fill_Vector.h"
#include "Mesh.h"
#include "Shader.h"
#include "Mesh_Renderer.h"

int main() {
    // --- Chargement du fichier obj dans nos classe ---
    FileReader lecteur("../Fichier_obj/jointure_v2.obj");
    Fill_Vector Tab (lecteur);
    Tab.export_data();
    const std::vector<std::array<float,3>>& points = Tab.getPoints();
    const std::vector<std::array<int,3>>& faces = Tab.getFaces();
    Mesh Me (points, faces);

    // -- Permet d'ouvrir la fenetre OpenGL --
    if (!glfwInit()) {
        std::cerr << "Erreur d'initialisation de GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Viewer - jointure_v2.obj", nullptr, nullptr);
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

    // -- Mets le shader et remplie les matrice pour l'affichage --
    Shader monShader("../vertex.glsl", "../fragment.glsl");
    Mesh_Renderer renderer(&monShader);
    
    renderer.set_buffer();
    renderer.updateFromMesh(&Me); // Envoie ton Mesh dans le VBO/EBO de la carte graphique !
    renderer.setRenderMode(RenderMode::WIREFRAME); // Affiche les arrete par défault

    // Boucle du programme 
    while (!glfwWindowShouldClose(window)) {
        // Raccourcis clavier pour tester les modes d'affichage
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
            renderer.setRenderMode(RenderMode::FILL);      // Plein
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
            renderer.setRenderMode(RenderMode::WIREFRAME); // arrete
        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
            renderer.setRenderMode(RenderMode::POINTS);    // Sommets

        // Effacer l'écran
        glClearColor(0.15f, 0.15f, 0.18f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Dessiner ton objet
        renderer.draw();

        // permet de recupere les valeur du clavier
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}