#pragma once
#include <glm/glm.hpp>

class Camera{
    public:
    glm::vec3 position;
    glm::vec3 rotation;
    float width = 640.0f;
    float height = 480.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    float fov = 45.0f;
    glm::mat4 getView();
    private:
};