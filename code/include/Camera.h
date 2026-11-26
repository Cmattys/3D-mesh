#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <array>

// Énumération pour gérer les déplacements au clavier
enum class Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Valeurs par défaut de la caméra
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float FOV         =  45.0f;

class Camera {
public:
    // Attributs définis dans le diagramme UML
    std::vector<float> position;
    std::vector<float> front;
    std::vector<float> up;
    std::vector<float> right;
    
    float yaw;
    float pitch;
    float fov;

    // Options de contrôle et repère monde
    std::vector<float> worldUp;
    float movementSpeed;
    float mouseSensitivity;

    
    // Constructeur avec valeurs par défaut
    Camera(std::vector<float> pos = {0.0f, 0.0f, 3.0f}, 
        std::vector<float> upVec = {0.0f, 1.0f, 0.0f}, 
        float startYaw = YAW, 
        float startPitch = PITCH);

    // Méthodes du diagramme UML
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspectRatio, float nearPlane = 0.1f, float farPlane = 100.0f) const;
    
    void processKeyboard(Direction direction, float deltaTime);
    void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
    void processMouseScroll(float yOffset);

    // Helpers pratiques pour envoyer directement un glm::vec3 au Shader ou à InteractionManager
    glm::vec3 getPositionVec3() const { return glm::vec3(position[0], position[1], position[2]); }
    glm::vec3 getFrontVec3() const    { return glm::vec3(front[0], front[1], front[2]); }
    glm::vec3 getUpVec3() const       { return glm::vec3(up[0], up[1], up[2]); }
    glm::vec3 getRightVec3() const    { return glm::vec3(right[0], right[1], right[2]); }

    float panSpeed = 0.2f; // À ajuster selon la taille de ton objet (en mm)

    void processMousePan(float xOffset, float yOffset);

    // ... tes attributs existants ...
    float nearPlane = 0.1f;
    float farPlane  = 1000.0f;

    // Ajuste automatiquement la position, les vitesses et les plans de coupe sur un maillage
    void focusOnMesh(const std::vector<std::array<float, 3>>& points);

private:
    // Recalcule les vecteurs front, right et up à partir des angles d'Euler (yaw, pitch)
    void updateCameraVectors();
};

