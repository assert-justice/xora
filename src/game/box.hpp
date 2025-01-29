#pragma once
#include "engine/engine.hpp"

class Box{
    public:
    Box(){};
    Box(Texture* texture, Shader* shader, Mesh* mesh);
    void draw(glm::vec3 position, glm::vec3 scale);
    void draw(glm::mat4 matrix);
    // private:
    // glm::mat4 model;
    Texture* texture;
    Shader* shader;
    Mesh* mesh;
};