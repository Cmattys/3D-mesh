#include "Mesh_Renderer.h"
#include "Camera.h"
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Mesh_Renderer::Mesh_Renderer(Shader* s) 
    : VAO(0), VBO(0), EBO(0), shader(s), renderMode(RenderMode::WIREFRAME), indexCount(0) {}

Mesh_Renderer::~Mesh_Renderer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh_Renderer::set_buffer() {
    // Génère les 3 objets OpenGL dans la carte graphique
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}

void Mesh_Renderer::updateFromMesh(Mesh* mesh) {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    // Dictionnaire pour retrouver rapidement l'indice (0, 1, 2...) d'un Vertex*
    std::unordered_map<Vertex*, unsigned int> vertexToIndex;

    const auto& meshVertices = mesh->getVertices(); // On récupère la référence via le getter

    vertices.reserve(meshVertices.size() * 3);
    for (size_t i = 0; i < meshVertices.size(); ++i) {
        Vertex* v = meshVertices[i];
        vertices.push_back(v->x);
        vertices.push_back(v->y);
        vertices.push_back(v->z);
        vertexToIndex[v] = static_cast<unsigned int>(i);
    }

    // -- Extraction des faces --
    const auto& meshFaces = mesh->getFaces(); // On récupère la référence via le getter

    indices.reserve(meshFaces.size() * 3);
    for (Face* f : meshFaces) {
        if (f->he == nullptr) continue;

        Vertex* v1 = f->he->target;
        Vertex* v2 = f->he->next->target;
        Vertex* v0 = f->he->next->next->target;

        indices.push_back(vertexToIndex[v0]);
        indices.push_back(vertexToIndex[v1]);
        indices.push_back(vertexToIndex[v2]);
    }
    // -----DEBUG --------
    std::cout << "[DEBUG MESH] Sommets : " << meshVertices.size() 
        << " | Indices : " << indexCount << std::endl;
if (!meshVertices.empty()) {
    std::cout << "[DEBUG MESH] Premier sommet : (" 
            << meshVertices[0]->x << ", " 
            << meshVertices[0]->y << ", " 
            << meshVertices[0]->z << ")" << std::endl;
}
    indexCount = indices.size();

    // 3. Envoyer tout ça dans les buffers OpenGL (VAO / VBO / EBO)
    glBindVertexArray(VAO);

    // Remplir le VBO avec les sommets (x, y, z)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Remplir l'EBO avec les indices des triangles
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Expliquer au VAO que le layout 0 contient des paquets de 3 floats (x, y, z)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Mesh_Renderer::setRenderMode(RenderMode mode) {
    renderMode = mode;
}

void Mesh_Renderer::draw(Camera* camera) {
    shader->use();

    // Récupération des matrices depuis l'instance de Camera
    // On passe 2000.0f en farPlane pour conserver la visibilité à l'échelle en mm
    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 proj = camera->getProjectionMatrix(1280.0f / 720.0f, camera->nearPlane, camera->farPlane);

    shader->setMat4("view", view);
    shader->setMat4("projection", proj);
    shader->setVec3("objectColor", glm::vec3(0.2f, 0.8f, 0.9f)); // Couleur bleu cyan

    // Choix du mode de rendu (Plein, Fil de fer, ou Points)
    if (renderMode == RenderMode::WIREFRAME) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else if (renderMode == RenderMode::POINTS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        glPointSize(5.0f);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    // Dessin du maillage
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}