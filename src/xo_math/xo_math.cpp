#include "xo_math.hpp"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 XoMath::popMat4()
{
    if(mat4Stack.size() == 0) return glm::mat4(1);
    auto res = peekMat4();
    mat4Stack.pop_back();
    return res;
}

glm::mat4 XoMath::peekMat4()
{
    if(mat4Stack.size() == 0) return glm::mat4(1);
    return mat4Stack[mat4Stack.size() - 1];
}

void XoMath::pushIdentity()
{
    mat4Stack.push_back(glm::mat4(1));
}

void XoMath::pushOrthographic(float left, float right, float bottom, float top, float near, float far)
{
    mat4Stack.push_back(glm::ortho(left, right, bottom, top, near, far));
}

void XoMath::pushPerspective(float fov, float aspect, float near, float far)
{
    mat4Stack.push_back(glm::perspective(fov, aspect, near, far));
}

void XoMath::pushMat4(glm::mat4 mat)
{
    mat4Stack.push_back(mat);
}

void XoMath::saveMat4(int id)
{
    mat4Store[id] = popMat4();
}

void XoMath::loadMat4(int id)
{
    if(mat4Store.count(id) == 0){
        pushIdentity();
    }
    else{
        pushMat4(mat4Store[id]);
    }
}

glm::vec3 XoMath::popVector3()
{
    if(vector3Stack.size() == 0) return glm::vec3();
    auto res = peekVector3();
    vector3Stack.pop_back();
    return res;
}

glm::vec3 XoMath::peekVector3()
{
    if(vector3Stack.size() == 0) return glm::vec3();
    return vector3Stack[vector3Stack.size() - 1];
}

void XoMath::pushVector3(float x, float y, float z)
{
    vector3Stack.push_back(glm::vec3(x, y, z));
}

void XoMath::saveVector3(int id)
{
    mat4Store[id] = popMat4();
}

void XoMath::loadVector3(int id)
{
    if(mat4Store.count(id) == 0) pushIdentity();
    else pushMat4(mat4Store[id]);
}

void XoMath::translate()
{
    auto vec = popVector3();
    auto mat = popMat4();
    mat = glm::translate(mat, vec);
    pushMat4(mat);
}

void XoMath::scale()
{
    auto vec = popVector3();
    auto mat = popMat4();
    mat = glm::scale(mat, vec);
    pushMat4(mat);
}

void XoMath::rotateEuler()
{
    auto vec = popVector3();
    auto mat = popMat4();
    mat = glm::rotate(mat, vec.x, glm::vec3(1,0,0));
    mat = glm::rotate(mat, vec.y, glm::vec3(0,1,0));
    mat = glm::rotate(mat, vec.z, glm::vec3(0,0,1));
    pushMat4(mat);
}

bool XoMath::initInternal()
{
    return true;
}

void XoMath::cleanupInternal()
{
}
