#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>


class Shader {
private:
    unsigned int ID;

public:
    Shader(const char* vertexPath, const char* fragmentPath);

    void use();
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setMat4(const std::string& name, const glm::mat4& matrix) const;
};