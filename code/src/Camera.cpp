#include "Camera.h"
#include <cmath>
#include <cfloat>

Camera::Camera(std::vector<float> pos, std::vector<float> upVec, float startYaw, float startPitch)
    : position(pos), 
    front({0.0f, 0.0f, -1.0f}), 
    worldUp(upVec), 
    yaw(startYaw), 
    pitch(startPitch), 
    fov(FOV),
    movementSpeed(SPEED), 
    mouseSensitivity(SENSITIVITY) 
{
    // Sécurité si les vecteurs passés n'ont pas 3 composantes
    if (position.size() < 3) position = {0.0f, 0.0f, 3.0f};
    if (worldUp.size() < 3)  worldUp  = {0.0f, 1.0f, 0.0f};
    
    up.resize(3);
    right.resize(3);
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    glm::vec3 pos = getPositionVec3();
    glm::vec3 f   = getFrontVec3();
    glm::vec3 u   = getUpVec3();
    return glm::lookAt(pos, pos + f, u);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio, float nearPlane, float farPlane) const {
    // Protection contre la division par zéro si la fenêtre est réduite
    if (aspectRatio <= 0.0f) aspectRatio = 1.0f; 
    return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

void Camera::processKeyboard(Direction direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    
    glm::vec3 pos = getPositionVec3();
    glm::vec3 f   = getFrontVec3();
    glm::vec3 r   = getRightVec3();
    glm::vec3 u   = getUpVec3();

    if (direction == Direction::FORWARD)
        pos += f * velocity;
    if (direction == Direction::BACKWARD)
        pos -= f * velocity;
    if (direction == Direction::LEFT)
        pos -= r * velocity;
    if (direction == Direction::RIGHT)
        pos += r * velocity;
    if (direction == Direction::UP)
        pos += u * velocity;
    if (direction == Direction::DOWN)
        pos -= u * velocity;

    position = {pos.x, pos.y, pos.z};
}

void Camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw   += xOffset;
    pitch += yOffset;

    // Évite le retournement de la caméra (Gimbal lock aux pôles)
    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::processMouseScroll(float yOffset) {
    fov -= yOffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

void Camera::updateCameraVectors() {
    // Calcul du nouveau vecteur Front via trigonométrie sphérique
    glm::vec3 f;
    f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = sin(glm::radians(pitch));
    f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    f = glm::normalize(f);

    glm::vec3 wUp(worldUp[0], worldUp[1], worldUp[2]);
    
    // Recalcul des vecteurs Right et Up orthogonaux
    glm::vec3 r = glm::normalize(glm::cross(f, wUp));
    glm::vec3 u = glm::normalize(glm::cross(r, f));

    front = {f.x, f.y, f.z};
    right = {r.x, r.y, r.z};
    up    = {u.x, u.y, u.z};
}
void Camera::processMousePan(float xOffset, float yOffset) {
    glm::vec3 pos = getPositionVec3();
    glm::vec3 r   = getRightVec3();
    glm::vec3 u   = getUpVec3();

    // Déplacement style CAO/Blender (on "attrape" la scène avec la souris)
    // Si tu trouves le sens inversé, remplace les "-=" par "+="
    pos -= r * (xOffset * panSpeed);
    pos -= u * (yOffset * panSpeed);

    position = {pos.x, pos.y, pos.z};
}

void Camera::focusOnMesh(const std::vector<std::array<float, 3>>& points) {
    if (points.empty()) return;

    // 1. Recherche des bornes min et max sur X, Y, Z
    glm::vec3 minPt(FLT_MAX);
    glm::vec3 maxPt(-FLT_MAX);

    for (const auto& p : points) {
        glm::vec3 v(p[0], p[1], p[2]);
        minPt = glm::min(minPt, v);
        maxPt = glm::max(maxPt, v);
    }

    // 2. Calcul du centre et de la diagonale de la boîte englobante
    glm::vec3 center = (minPt + maxPt) * 0.5f;
    float diagonal   = glm::length(maxPt - minPt);

    // Sécurité si tous les points sont confondus
    if (diagonal <= 0.0f) diagonal = 1.0f;

    // 3. Positionnement de la caméra face au centre avec une légère plongée
    glm::vec3 newPos = center + glm::vec3(0.0f, diagonal * 0.3f, diagonal * 1.5f);
    position = {newPos.x, newPos.y, newPos.z};

    // 4. Orientation : regarde exactement vers le centre de l'objet
    glm::vec3 dir = glm::normalize(center - newPos);
    yaw   = glm::degrees(atan2(dir.z, dir.x));
    pitch = glm::degrees(asin(dir.y));
    updateCameraVectors();

    // 5. Adaptation automatique des vitesses et de la profondeur de champ
    movementSpeed = diagonal * 0.5f;
    panSpeed      = diagonal * 0.002f;
    nearPlane     = diagonal * 0.001f;
    farPlane      = diagonal * 10.0f;
}