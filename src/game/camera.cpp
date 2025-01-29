#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera::getView()
{
    auto mat = glm::perspective(glm::radians(fov), width / height, nearPlane, farPlane);
    mat = glm::rotate(mat, rotation.x, glm::vec3(1, 0, 0));
    mat = glm::rotate(mat, rotation.y, glm::vec3(0, 1, 0));
    mat = glm::rotate(mat, rotation.z, glm::vec3(0, 0, 1));
    mat = glm::translate(mat, position);
    return mat;
}
