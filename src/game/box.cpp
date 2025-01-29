#include "box.hpp"
#include <glm/gtc/matrix_transform.hpp>

Box::Box(Texture *tex, Shader *sh, Mesh* me)
{
    texture = tex;
    shader = sh;
    mesh = me;
}

void Box::draw(glm::vec3 position, glm::vec3 scale)
{
    glm::mat4 mat(1);
    mat = glm::translate(mat, position);
    mat = glm::scale(mat, scale);

    draw(mat);
}

void Box::draw(glm::mat4 matrix)
{
    shader->use();
    texture->use();
    shader->setUniform("world", matrix);
    mesh->draw();
}
