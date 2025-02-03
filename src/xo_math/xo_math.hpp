#pragma once
#include <unordered_map>
#include <vector>
#include "engine/module.hpp"
#include "glm/glm.hpp"

class XoMath : public Module {
    public:
    glm::mat4 popMat4();
    glm::mat4 peekMat4();
    void pushIdentity();
    void pushOrthographic(float left, float right, float bottom, float top, float near, float far);
    void pushPerspective(float fov, float aspect, float near, float far);
    void pushMat4(glm::mat4 mat);
    void saveMat4(int id);
    void loadMat4(int id);
    glm::vec3 popVector3();
    glm::vec3 peekVector3();
    void pushVector3(float x, float y, float z);
    void saveVector3(int id);
    void loadVector3(int id);
    void translate();
    void scale();
    void rotateEuler();
    protected:
    bool initInternal();
    void cleanupInternal();
    private:
    std::unordered_map<int, glm::mat4> mat4Store;
    std::unordered_map<int, glm::vec3> vector3Store;
    std::vector<glm::mat4> mat4Stack;
    std::vector<glm::vec3> vector3Stack;
};
