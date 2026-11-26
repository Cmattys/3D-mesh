#pragma once

#include <GL/glew.h>
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"

class Camera;

enum class RenderMode {
    FILL,
    WIREFRAME,
    POINTS
};

class Mesh_Renderer {
private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    Shader* shader;
    RenderMode renderMode;
    int indexCount;

public:
    Mesh_Renderer(Shader* s);
    ~Mesh_Renderer();

    void set_buffer();
    void updateFromMesh(Mesh* mesh);
    void draw(Camera* camera);
    void setRenderMode(RenderMode mode); // Le setter officiel de ton UML !
};
