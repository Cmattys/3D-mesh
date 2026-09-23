#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    // Initialisation de GLFW
    if (!glfwInit()) {
        std::cerr << "Échec de l'initialisation de GLFW" << std::endl;
        return -1;
    }

    // Création de la fenêtre (Largeur, Hauteur, Titre)
    GLFWwindow* window = glfwCreateWindow(800, 600, "Mesh Viewer 3D", NULL, NULL);
    if (!window) {
        std::cerr << "Échec de la création de la fenêtre GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Lier le contexte OpenGL de la fenêtre au thread principal
    glfwMakeContextCurrent(window);

    // Initialisation de GLEW (doit être fait après avoir créé le contexte OpenGL)
    if (glewInit() != GLEW_OK) {
        std::cerr << "Échec de l'initialisation de GLEW" << std::endl;
        return -1;
    }

    // Boucle de rendu principale
    while (!glfwWindowShouldClose(window)) {
        // Définir la couleur de fond (RGB : gris foncé) et effacer l'écran
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Échanger les buffers pour afficher l'image
        glfwSwapBuffers(window);
        
        // Traiter les événements (clavier, souris, redimensionnement)
        glfwPollEvents();
    }

    // Nettoyer et fermer proprement
    glfwTerminate();
    return 0;
}